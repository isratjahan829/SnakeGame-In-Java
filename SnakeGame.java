package GameProject;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

@SuppressWarnings("serial")
public class SnakeGame extends JPanel implements ActionListener {
    private final int WIDTH = 600;
    private final int HEIGHT = 500;
    private final int DOT_SIZE = 10;
    private final int ALL_DOTS = 900;
    private final int RAND_POS = 29;
    private final int DELAY = 140;

    private final int x[] = new int[ALL_DOTS];
    private final int y[] = new int[ALL_DOTS];

    private int dots;
    private int appleX;
    private int appleY;

    private boolean leftDirection = false;
    private boolean rightDirection = true;
    private boolean upDirection = false;
    private boolean downDirection = false;
    private boolean inGame = true;

    private Timer timer;

    public SnakeGame() {
        initGame();
    }

    private void initGame() {
        addKeyListener(new TAdapter());
        setBackground(Color.black);
        setFocusable(true);

        setPreferredSize(new Dimension(WIDTH, HEIGHT));
        initSnake();
        placeApple();

        timer = new Timer(DELAY, this);
        timer.start();
    }

    private void initSnake() {
        dots = 3;

        for (int i = 0; i < dots; i++) {
            x[i] = 50 - i * DOT_SIZE;
            y[i] = 50;
        }
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        doDrawing(g);
    }

    private void doDrawing(Graphics g) {
        if (inGame) {
            g.setColor(Color.red);
            g.fillOval(appleX, appleY, DOT_SIZE, DOT_SIZE);

            for (int i = 0; i < dots; i++) {
                if (i == 0) {
                    g.setColor(Color.green);
                } else {
                    g.setColor(Color.orange);
                }

                g.fillRect(x[i], y[i], DOT_SIZE, DOT_SIZE);
            }

            Toolkit.getDefaultToolkit().sync();

        } else {
            gameOver(g);
        }
    }

    private void gameOver(Graphics g) {
        String message = "Game Over";
        Font font = new Font("Helvetica", Font.BOLD, 14);
        FontMetrics metrics = getFontMetrics(font);

        g.setColor(Color.white);
        g.setFont(font);
        g.drawString(message, (WIDTH - metrics.stringWidth(message)) / 2, HEIGHT / 2);
    }

    private void checkApple() {
        if ((x[0] == appleX) && (y[0] == appleY)) {
            dots++;
            placeApple();
        }
    }

    private void move() {
        for (int i = dots; i > 0; i--) {
            x[i] = x[i - 1];
            y[i] = y[i - 1];
        }

        if (leftDirection) {
            x[0] -= DOT_SIZE;
        }

        if (rightDirection) {
            x[0] += DOT_SIZE;
        }

        if (upDirection) {
            y[0] -= DOT_SIZE;
        }

        if (downDirection) {
            y[0] += DOT_SIZE;
        }
    }

    private void checkCollision() {
        for (int i = dots; i > 0; i--) {
            if ((i > 4) && (x[0] == x[i]) && (y[0] == y[i])) {
                inGame = false;
            }
        }

        if (y[0] >= HEIGHT) {
            inGame = false;
        }

        if (y[0] < 0) {
            inGame = false;
        }

        if (x[0] >= WIDTH) {
            inGame = false;
        }

        if (x[0] < 0) {
            inGame = false;
        }

        if (!inGame) {
            timer.stop();
        }
    }

    private void placeApple() {
        int r = (int) (Math.random() * RAND_POS);
        appleX = r * DOT_SIZE;

        r = (int) (Math.random() * RAND_POS);
        appleY = r * DOT_SIZE;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (inGame) {
            checkApple();
            checkCollision();
            move();
        }

        repaint();
    }

    private class TAdapter extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            int key = e.getKeyCode();

            if ((key == KeyEvent.VK_LEFT) && (!rightDirection)) {
                leftDirection = true;
                upDirection = false;
                downDirection = false;
            }

            if ((key == KeyEvent.VK_RIGHT) && (!leftDirection)) {
                rightDirection = true;
                upDirection = false;
                downDirection = false;
            }

            if ((key == KeyEvent.VK_UP) && (!downDirection)) {
                upDirection = true;
                rightDirection = false;
                leftDirection = false;
            }

            if ((key == KeyEvent.VK_DOWN) && (!upDirection)) {
                downDirection = true;
                rightDirection = false;
                leftDirection = false;
            }
        }
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Snake Game");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(new SnakeGame());
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}
