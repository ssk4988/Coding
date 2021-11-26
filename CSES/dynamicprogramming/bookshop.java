import java.io.*;
import java.util.*;

public class bookshop {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numBooks = Integer.parseInt(tokenizer.nextToken());
        int maxCost = Integer.parseInt(tokenizer.nextToken());
        Book[] books = new Book[numBooks];
        tokenizer = new StringTokenizer(in.readLine());
        StringTokenizer tokenizer2 = new StringTokenizer(in.readLine());
        for(int i = 0; i < numBooks; i++){
            int price = Integer.parseInt(tokenizer.nextToken());
            int pagenum = Integer.parseInt(tokenizer2.nextToken());
            books[i] = new Book(pagenum, price);
        }
        Arrays.sort(books);
        int[] pagesPerPrice = new int[maxCost + 1];
        for(int i = 0; i < numBooks; i++){
            int price = books[i].price;
            int page = books[i].pages;
            for(int j = maxCost; j >= 0; j--){
                if(j - price >= 0 && pagesPerPrice[j] < page + pagesPerPrice[j - price]){
                    pagesPerPrice[j] = page + pagesPerPrice[j - price];
                }
            }
        }
        System.out.println(pagesPerPrice[maxCost]);

        in.close();
    }
    public static class Book implements Comparable<Book> {
        int pages;
        int price;
        public Book(int pages, int price){
            this.pages = pages;
            this.price = price;
        }
        @Override
        public int compareTo(bookshop.Book o) {
            return this.pages - o.pages;
        }
    }
}