import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Collections;
import java.util.Scanner;

public class Main {
    static class Obj {
        public int weight;
        public int price;

        public Obj() {
            weight = 0;
            price = 0;
        }
    };

    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, w;
        Obj[] objs;

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                w = sc.nextInt();
                objs = new Obj[n];
                for (int i = 0; i < n; i++) {
                    objs[i] = new Obj();
                    objs[i].weight = sc.nextInt();
                    objs[i].price = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(double result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%.4f\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void sortByProfit(Obj[] objs) {
            for(int i = 0; i < objs.length - 1; ++i) {
                double o1 = objs[i].price / objs[i].weight;
                for (int j = i + 1; j < objs.length; ++j) {
                    double o2 = objs[j].price / objs[j].weight;
                    if (o1 < o2) {
                        int auxW = objs[j].weight;
                        int auxP = objs[j].price;
                        objs[j].weight = objs[i].weight;
                        objs[j].price = objs[i].price;
                        objs[i].weight = auxW;
                        objs[i].price = auxP;
                    }
                }
            }

            for (Obj o : objs) {
                System.out.println(o.weight + " " + o.price);
            }
        }

        private double getResult() {
            // TODO: Aflati profitul maxim care se poate obtine cu
            // obiectele date.
            sortByProfit(objs);

            double weight = 0;
            double profit = 0.0;
            int lastIndex = 0;
            int i = 0;

            System.out.println("AICI");

            while (weight < w && i < objs.length) {
                if (objs[i].weight > w) {
                    double left = w - weight;
                    double x = left;
                    profit += (x / objs[lastIndex].weight) * objs[lastIndex].price;
                    weight = w;
                }
                if (weight + objs[i].weight <= w) {
                    profit += objs[i].price;
                    weight += objs[i].weight;
                    ++i;
                } else {
                    lastIndex = i;
                    break;
                }
            }

            if (weight < w) {
                System.out.println(lastIndex);
                System.out.println("AICI2");
                double left = w - weight;
                System.out.println(left);
                double x = left;
                System.out.println(objs[lastIndex].weight);
                profit += (x / objs[lastIndex].weight) * objs[lastIndex].price;
            }

            System.out.println(profit);
            return profit;
        }

        public void solve() {
            readInput();
            writeOutput(getResult());
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
