import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class Main {
    static class Homework {
        public int deadline;
        public int score;

        public Homework() {
            deadline = 0;
            score = 0;
        }

        public int compareTo(Homework o1) {
            if (this.deadline > o1.deadline) {
                return 1;
            } else {
                return -1;
            }
        }
    }

    static class Cmp implements Comparator<Homework> {
        @Override
        public int compare(Homework o1, Homework o2) {
            if (o1.score < o2.score) {
                return 1;
            } else {
                return -1;
            }
        }
    }



    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n;
        Homework[] hws;

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                hws = new Homework[n];
                for (int i = 0; i < n; i++) {
                    hws[i] = new Homework();
                    hws[i].deadline = sc.nextInt();
                    hws[i].score = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int getResult() {
            // TODO: Aflati punctajul maxim pe care il puteti obtine
            // planificand optim temele.
            // ; // sort by score
            for(int i = 0; i < hws.length - 1; ++i) {
                for (int j = i + 1; j < hws.length; ++j) {
                    if (hws[i].compareTo(hws[j]) < 0) {
                        int auxDL = hws[i].deadline;
                        int auxSC = hws[i].score;
                        hws[i].deadline = hws[j].deadline;
                        hws[i].score = hws[j].score;
                        hws[j].deadline = auxDL;
                        hws[j].score = auxSC;
                    }
                }
            }

            for(Homework s : hws) {
                System.out.println(s.deadline + " " + s.score);
            }

            Queue<Homework> pw = new PriorityQueue<>(hws.length, new Cmp()); // sort by score
//            for(Homework s : pw) {
//                System.out.println(s.deadline + " " + s.score);
//            }

            int iterate = hws[0].deadline;
            int score = 0;
            int i = 0;

            while (iterate >= 1) { // pana la dl din sapt 1
                while (i < hws.length && iterate <= hws[i].deadline) {
                    // System.out.println("ADDING" + hws[i].deadline + " " + hws[i].score);
                        pw.add(hws[i]);
                        i += 1;
                }
                // System.out.println("ADDING SCORE" + pw.peek().score);
                score += pw.poll().score;
                --iterate;
            }

            return score;
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
