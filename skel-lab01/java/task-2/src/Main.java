import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        double n;

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextDouble();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(double x) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%.4f\n", x);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private double computeSqrt() {
            // TODO: Calculeaza sqrt(n) cu o precizie de 10^-3.
            // Precizie de 10^(-x) inseamna |valoarea_ta - valoarea_reala| < 10^(-x).
            double start = 0, end = n;
            double mid;
            double root = 0.0;
            if (n < 1) {
                ++end;
            }
            while (start <= end) {
                mid = (start + end) / 2;
                if (Math.abs(n - mid * mid) < 0.0001) {
                    root = mid;
                    break;
                } else if (mid * mid < n || (mid * mid < n && mid < 1)){
                    start = mid;
                    root = mid;
                } else if (mid * mid > n || (mid * mid > n && mid < 1)){
                    end = mid;
                }
            }

            return root;
        }

        public void solve() {
            readInput();
            writeOutput(computeSqrt());
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
