/*
  quine.java
  Is the Name of This Problem, MCPC 2012 Problem D
  Java solution by Gabriel Foust
*/

import java.io.*;
import java.util.*;

public class quine
{
    public static void main( String[] args ) throws FileNotFoundException
    {
        Scanner scanner= new Scanner( new File( "quine.in" ) );
        
        String line;

        line= scanner.nextLine();
        while (!line.equals( "END" ))
        {
            if (line.length() >= 5 &&
                line.charAt( 0 ) == '"' &&
                line.charAt( line.length()/2 ) == '"' &&
                line.charAt( line.length()/2 + 1 ) == ' ')
            {
                String A = line.substring( 1, line.length()/2 );
                String B = line.substring( line.length()/2 + 2 );

                if (A.equals( B ) && !A.contains( "\"" ))
                {
                    System.out.printf( "Quine(%s)", A );
                    System.out.println();
                }
                else
                    System.out.println( "not a quine" );
            }
            else
                System.out.println( "not a quine" );

            line= scanner.nextLine();
        }
    }
}