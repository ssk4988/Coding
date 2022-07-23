#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point{
    int x;
    int y;
};

struct point subtract(struct point a, struct point b) {
    struct point result;
    result.x = a.x-b.x;
    result.y = a.y-b.y;
    return result;
};

int cross(struct point a, struct point b){
    return a.x*b.y-b.x*a.y;
}

int side(struct point a, struct point b, struct point c){
    struct point line = subtract(b, a);
    struct point vector = subtract(c, a);
    return cross(line, vector);
}

double area(struct point polygon[], int n){
    double result = 0;
    int i;
    
    for (i = 0; i < n; i++) {
        struct point a = polygon[i];
        struct point b = polygon[(i+1)%n];
        result += (double)((b.x-a.x)*(b.y+a.y));
    }
    return fabs(result)/2.0;
}

int main()
{
    int t;
    scanf("%d", &t);

    for (int q = 0; q < t; q++) {
        int n, m, i, j, k;
        scanf("%d%d", &n, &m);
        
        struct point polygon[n];
        for (i = 0; i < n; i++) {
            scanf("%d%d", &polygon[i].x, &polygon[i].y);
        }
        
        struct point toppings[m];
        for (i = 0; i < m; i++) {
            scanf("%d%d", &toppings[i].x, &toppings[i].y);
        }
        
        int found_ans = 0;
        double ans = 999999999999;
        for (i = 0; i < n; i++) {
            for (j = i + 2; j < n; j++) {
                int num_meghan = 0;
                int num_natalie = 0;
                int good = 1;
                
                for (k = 0; k < m; k++) {
                    int s = side(polygon[i], polygon[j], toppings[k]);
                    if (s == 0) good = 0;
                    else if(s < 0) num_meghan++;
                    else num_natalie++;
                }
                
                if (!good || num_natalie != num_meghan) {
                    continue;
                }
                
                struct point polygon_meghan[j-i+1];
                int count;
                count = 0;
                for (k = i; k <= j; k++, count++){
                    polygon_meghan[count] = polygon[k];
                } 
                double area_meghan = area(polygon_meghan, j-i+1);
                
                struct point polygon_natalie[n-(j-i-1)];
                count = 0;
                for (k = j; k < n; k++, count++){
                    polygon_natalie[count] = polygon[k];
                }
                for (k = 0; k <= i; k++, count++){
                    polygon_natalie[count] = polygon[k];
                }
                double area_natalie = area(polygon_natalie, n-(j-i-1));
                
                found_ans++;
                double difference = fabs(area_natalie-area_meghan);
                if (difference < ans) {
                    ans = difference;
                }
            }
        }
        
        if (found_ans) {
            printf("Yes\n%f\n\n", ans);
        }
        else {
            printf("No\n\n");
        }
    }
    return 0;
}

