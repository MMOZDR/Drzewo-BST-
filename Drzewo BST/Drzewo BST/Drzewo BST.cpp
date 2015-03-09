#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include "conio.h"
#include "time.h"
#include "math.h"

class DrzewoBST{

protected:

struct Wezel  {
   int klucz;
   Wezel *Lewy;
   Wezel *Prawy;
 };

struct Info{
	Wezel *root;
};

Info inf;

public:

Wezel *ion (Wezel *root, int X)   {
    if (root == NULL || X == root->klucz)
          return root;

 if (X < root->klucz)
          return ion (root->Lewy, X);
 else
          return ion (root->Prawy, X);
};

int szukaj (Wezel *root, int X);
int dodaj (Wezel *&root, int X);
void dodajN (int N);
int wyswietl (Wezel *root);
Wezel *&rootinfo(){return inf.root;};



Wezel *min(Wezel *root){
	while (root->Lewy!=NULL){
		root=root->Lewy;
	}
	return root;
};

Wezel *max(Wezel *root){
	while (root->Prawy!=NULL){
		root=root->Prawy;
	}
	return root;
};

Wezel *usun(Wezel *root, int data)
{
	  Wezel *p=ion(root,data);
        Wezel *temp;
        if(p==NULL)
        {
                printf("Nie ma takiego wezla w drzewie!\n");
        }
        else if(data < root->klucz)
        {
                root->Lewy = usun(root->Lewy, data);
        }
        else if(data > root->klucz)
        {
                root->Prawy = usun(root->Prawy, data);
        }
        else
        {
                if(root->Prawy && root->Lewy)
                {
					int zm=0;
					printf("Wybierz rodzaj usuwania:\n");
					printf("0 - wzgledem poprzednika;\n");
					printf("1 - wzgledem nastepnika;\n");
	                scanf("%d",&zm);

					if(zm==0){
						printf("Wybrano usuwanie wzgledem poprzednika!\n"); 
						temp = max(root->Lewy);
						root -> klucz = temp->klucz; 
                        root -> Lewy = usun(root->Lewy,temp->klucz);
					}
					if(zm!=0){
						printf("Wybrano usuwanie wzgledem nastepnika!\n"); 
						temp = min(root->Prawy);
						root -> klucz = temp->klucz; 
                        root -> Prawy = usun(root->Prawy,temp->klucz);
						}
                }
                else
                {
                        temp = root;
                        if(root->Lewy == NULL)
                                root = root->Prawy;
                        else if(root->Prawy == NULL)
                                root = root->Lewy;
                        free(temp);  
                }
        }
        return root;
}

DrzewoBST(){printf("Stworzono drzewo!\n"); inf.root=NULL;};
~DrzewoBST(){};
};

int DrzewoBST::szukaj (Wezel *root, int X)   {
	if (root==NULL){printf("Drzewo jest puste!\n");return 1;}
	else
   if (ion(root,X)==NULL)  {
   printf("Brak wezla %d w drzewie! \n",X);
   return 1;
   }else
   printf("Wezel %d jest w drzewie! \n",X);
   return 0;
};

int DrzewoBST::dodaj (Wezel *&root, int X) {

	if(ion(root,X)!=NULL){return 1;}
	else{
	Wezel *y=NULL;
	Wezel *x=root;
	Wezel *a;
	a=(Wezel*)malloc(sizeof(Wezel));
	a->klucz=X;
	a->Lewy=a->Prawy=NULL;
	while(x!=NULL){
		y=x;
		if(a->klucz < x->klucz){
			x=x->Lewy;
		}else
			x=x->Prawy;
	}
	
	if(y==NULL){
		root=a;
	}else
		if(a->klucz<y->klucz){
		y->Lewy=a;
		}else
			y->Prawy=a;
		return 0;
	}
};

int DrzewoBST::wyswietl (Wezel *root){
	if (inf.root==NULL){printf("Drzewo jest puste!\n");return 1;}
	if (root != NULL){
         wyswietl (root->Lewy);
         printf("%d, ",root->klucz);
         wyswietl (root->Prawy);
	}
  return 0;
};

void DrzewoBST::dodajN (int N) {
	for (int i=0;i<N;i++){
		dodaj(rootinfo(),10+((rand()%1000+1)*(rand()%1000+1)));
	}
	
};




int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int X, k1, k2, k3, k4;
	FILE* fp = fopen("inlab03.txt", "r");
	if (fp == NULL)return -1;    
	fscanf (fp, "%d %d %d %d %d", &X, &k1, &k2, &k3, &k4);
	fclose(fp);
	
	clock_t begin, end;
	double time_spent;
	begin = clock();
    DrzewoBST g;
	g.usun(g.rootinfo(),k1);
	g.dodajN(X);
	g.dodaj(g.rootinfo(),k1);
	g.dodaj(g.rootinfo(),k2);
	g.dodaj(g.rootinfo(),k3);
	g.dodaj(g.rootinfo(),k4);
	g.usun(g.rootinfo(),k1);
	g.szukaj(g.rootinfo(),k1);
	g.usun(g.rootinfo(),k2);
	g.usun(g.rootinfo(),k3);
	g.usun(g.rootinfo(),k4);
    end = clock();
	printf("Czas: %f \n",(double)(end -begin) / CLOCKS_PER_SEC);
	_getche();
	return 0;
}
