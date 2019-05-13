#include < iostream >
#include < cmath >
#define POP 0
#define ADD 1

using namespace std;

int strlen(char s[]) {
   int size = 0;
   while (true) {
      if (s[size] == '\0')
         return size;
      size++;
   }
}
int charToInt(char c) {
   //return c - 'a';
   if (c == '1')
      return 1;
   if (c == '2')
      return 2;
   if (c == '3')
      return 3;
   if (c == '4')
      return 4;
   if (c == '5')
      return 5;
   if (c == '6')
      return 6;
   if (c == '7')
      return 7;
   if (c == '8')
      return 8;
   if (c == '9')
      return 9;
}

class Block {
public:
   int currSize;
   int size;
   int bunza;
   int bunmo;
   Block() {
      init();
   }
   void init() {
      size = 1;
      bunza = 0;
      bunmo = 0;
      currSize = 0;
   }
   void push(int n) {
      if (size == 1)
         setBunza(n);
      else if (size == 2) {
         if (bunza == 0)
            setBunza(n);
         else
            setBunmo(n);
      }
      currSize++;
   }
   void setBunza(int n) {
      bunza = n;
   }
   void setBunmo(int n) {
      bunmo = n;
   }
};

Block blocks[6][6];
int rowsCands[6];
int colsCands[6];
int padsCands[6];
int T;

void printAnswer() {
   int cnt = 0;
   for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++) {
         if (blocks[i][j].size == 1) {
            cout << blocks[i][j].bunza << " ";
         }
         else if (blocks[i][j].size == 2) {
            cout << blocks[i][j].bunza << "/" << blocks[i][j].bunmo << " ";
         }
         cnt++;
      }
      cout << endl;
   }
}

void updateCands(int& cands, int n, int type) {
   if (type == POP) 
      cands &= ~(1 << n);
   else if (type == ADD)
      cands |= (1 << n);
}

int getPadCandIndex(int y, int x) {
   int padCandIndex;

   if (y < 2 && x < 3)
      padCandIndex = 0;
   else if (y < 2 && x < 6)
      padCandIndex = 1;
   else if (y < 4 && x < 3)
      padCandIndex = 2;
   else if (y < 4 && x < 6)
      padCandIndex = 3;
   else if (y < 6 && x < 3)
      padCandIndex = 4;
   else if (y < 6 && x < 6)
      padCandIndex = 5;

   return padCandIndex;
}

void allUpdateCands(int y, int x, int n, int type) {
   int padCandIndex = getPadCandIndex(y, x);
   updateCands(rowsCands[y], n, type);
   updateCands(colsCands[x], n, type);
   updateCands(padsCands[padCandIndex], n, type);
}


void init() {
   for (int i = 0; i < 6; i++)
      rowsCands[i] = 0b1111111110;
   for (int i = 0; i < 6; i++)
      colsCands[i] = 0b1111111110;
   for (int i = 0; i < 6; i++)
      padsCands[i] = 0b1111111110;

   for(int i=0; i<6; i++)
      for (int j = 0; j < 6; j++) {
         int padCandIndex = getPadCandIndex(i, j);
         if (blocks[i][j].size == 1) {
            if (blocks[i][j].bunza != 0) {
               updateCands(rowsCands[i], blocks[i][j].bunza, POP);
               updateCands(colsCands[j], blocks[i][j].bunza, POP);
               updateCands(padsCands[padCandIndex], blocks[i][j].bunza, POP);
            }
         }
         else if (blocks[i][j].size == 2) {
            if (blocks[i][j].bunza != 0) {
               updateCands(rowsCands[i], blocks[i][j].bunza, POP);
               updateCands(colsCands[j], blocks[i][j].bunza, POP);
               updateCands(padsCands[padCandIndex], blocks[i][j].bunza, POP);
            }
            if (blocks[i][j].bunmo != 0) {
               updateCands(rowsCands[i], blocks[i][j].bunmo, POP);
               updateCands(colsCands[j], blocks[i][j].bunmo, POP);
               updateCands(padsCands[padCandIndex], blocks[i][j].bunmo, POP);
            }
         }
      }
}

int getCands(int y, int x) {
   int ret;

   int padCandIndex = getPadCandIndex(y, x);
   ret = (rowsCands[y] & colsCands[x]) & padsCands[padCandIndex];

   if (blocks[y][x].size == 2) {
      if (blocks[y][x].bunmo != 0)
         ret &= ((int)pow(2, blocks[y][x].bunmo) - 2);
      if (blocks[y][x].bunza != 0)
         ret &= (~((int)pow(2, blocks[y][x].bunza + 1) - 1));
   }

   return ret;
}

bool nextBlockTry() {

   for (int i = 0; i < 6; i++)
      for (int j = 0; j < 6; j++) {
         int currCands = getCands(i, j);
         int remainCount = blocks[i][j].size - blocks[i][j].currSize;
         int padCandIndex = getPadCandIndex(i, j);

         if (remainCount > 0) {
            for (int k = 1; k < 10; k++) {
               if (currCands & (1 << k)) {
                  Block orig = blocks[i][j];
                  allUpdateCands(i, j, k, POP);
                  blocks[i][j].push(k);
                  if (nextBlockTry())
                     return true;
                  allUpdateCands(i, j, k, ADD);
                  blocks[i][j] = orig;
               }
            }
            return false;
         }
      }

   return true;
}

void solve() {
   for (int i = 0; i < 6; i++)
      for (int j = 0; j < 6; j++) {

         int currCands = getCands(i, j);
         int remainCount = blocks[i][j].size - blocks[i][j].currSize;
         int padCandIndex = getPadCandIndex(i, j);

         if (remainCount > 0) {
            for (int k = 1; k < 10; k++) {
               if (currCands & (1 << k)) {
                  Block orig = blocks[i][j];
                  allUpdateCands(i, j, k, POP);
                  blocks[i][j].push(k);
                  if (nextBlockTry()) {
                     printAnswer();
                     return;
                  }
                  allUpdateCands(i, j, k, ADD);
                  blocks[i][j] = orig;
               }
            }
         }
      }
}


int main() {
   scanf("%d", &T);
   for (int tc = 1; tc <= T; tc++) {
      int cnt = 0;
      for (int i = 0; i < 6; i++)
         for (int j = 0; j < 6; j++) {
            char tmp[4];
            scanf("%s", tmp);
            if (strlen(tmp) == 1) {
               if (tmp[0] != '-') {
                  blocks[i][j].setBunza(charToInt(tmp[0]));
                  blocks[i][j].size = 1;
                  blocks[i][j].currSize++;
               }
               cnt++;
            }
            else if (strlen(tmp) == 3) {
               if (tmp[0] != '-') {
                  blocks[i][j].setBunza(charToInt(tmp[0]));
                  blocks[i][j].currSize++;
               }
               if (tmp[2] != '-') {
                  blocks[i][j].setBunmo(charToInt(tmp[2]));
                  blocks[i][j].currSize++;
               }
               blocks[i][j].size = 2;
               cnt++;
            }
         }
      printf("#%d\n", tc);
      init();
      solve();
      for (int i = 0; i < 6; i++)
         for (int j = 0; j < 6; j++)
            blocks[i][j].init();
   }
   return 0;
}
