#include <stdio.h>
#include <limits.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
const unsigned int x = 6;
const unsigned int y = 9; //one extra for null character '\0'

char data[x][y] = {
    "********",
    "* *",
    "* *** *",
    "* *",
    "* *",
    "********"
};

    int result[x][y] = {0}; //initialise to 0
    int vis[x][y] = {0};
    int qx[x*y] = {0}; //queue for x coordinates
    int qy[x*y] = {0}; //queue for y coordinates
    int qIndex = -1; //latest position of the queue
    int newItemsCount = 0; //new items in the queue

int updateQueue(int ni, int nj, int c){
if(ni >= x || nj >= y || ni < 0 || nj < 0){
    return 0;
    }
    else if(!vis[ni][nj]){
        qx[c] = ni;
        qy[c] = nj;
        newItemsCount++;
        return 1;
        }
        return 0;
}

void calculateDistance(int distance){

int c = qIndex + newItemsCount;
int count = c;
newItemsCount = 0;
do{
int ni, nj;
int i = qx[qIndex];
int j = qy[qIndex];
vis[i][j] = 1;
if(data[i][j] == ' '){
result[i][j] = distance;
//right side
ni = i; nj = j + 1;
c+=updateQueue(ni,nj,c);

//left side
ni = i; nj = j - 1;
c+=updateQueue(ni,nj,c);

//down
ni = i + 1; nj = j;
c+=updateQueue(ni,nj,c);

//up
ni = i - 1; nj = j;
c+=updateQueue(ni,nj,c);
}
qIndex++;
}while(qIndex != count);
//there are more children to take care of
if(newItemsCount > 0){
calculateDistance(distance + 1);
}

}
int main(){

for(int i = 0; i < x; i++){
for(int j = 0; j < y; j++){
result[i][j] = INT_MAX; //initialise to max distance
}
}
// will start from 1, 1 --- the first location where can go which will be said to be 'A'
qx[qIndex + 1] = 1;
qy[qIndex + 1] = 1;
qIndex++;
newItemsCount = 1;
calculateDistance(0);
for(int i = 0; i < x; i++){
for(int j = 0; j < y; j++){
if(result[i][j] != INT_MAX){
printf("%c", 'A' + result[i][j]);
} else{
printf("%c",data[i][j]);
}
}
printf("\n");
}
return 0;
}