#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void labirentYaz(int satir,int sutun,int matris[satir][sutun]);

int kontrol(int x,int y,int satir,int sutun);

int i,j;

struct Dugum
{
    int x;
    int y;
    struct Dugum *sonraki;
};

struct Dugum* kok = NULL;
struct Dugum* yedek;


struct Dugum* YeniDugum(int x,int y)
{
    struct Dugum* yigindugum = malloc(sizeof(struct Dugum));
    yigindugum->x = x;
    yigindugum->y =y;
    yigindugum->sonraki = NULL;
    return yigindugum;
}
///PUSH
void ekle(struct Dugum** kok, int x,int y)
{
    struct Dugum* yigindugum = YeniDugum(x,y);
    yigindugum->sonraki = *kok;
    *kok = yigindugum;
}
///POP
void al(struct Dugum** kok)
{
    struct Dugum* alinacak = *kok;
    *kok = (*kok)->sonraki;
    free(alinacak);
}

void yolBul(int girisX,int girisY,int cikisX,int cikisY,int satir,int sutun,int matris[satir][sutun])
{


    ///SAG
    if(matris[girisX][girisY+1]==1 && (girisY+1)<sutun)
    {
        girisY++;
        matris[girisX][girisY]=2;
        ekle(&kok,girisX,girisY);
        yolBul( girisX,girisY,cikisX,cikisY,satir,sutun,matris);
    }
    ///ASAGI
    else if(matris[girisX+1][girisY]==1  && (girisX+1)<satir)
    {

        girisX++;
        matris[girisX][girisY]=2;
        ekle(&kok,girisX,girisY);
        yolBul( girisX,girisY,cikisX,cikisY,satir,sutun,matris);
    }
    ///SOL
    else if(matris[girisX][girisY-1]==1 && (girisY-1)<sutun && -1<(girisY-1))
    {
        girisY--;
        matris[girisX][girisY]=2;
        ekle(&kok,girisX,girisY);
        yolBul( girisX,girisY,cikisX,cikisY,satir,sutun,matris);
    }
    ///YUKARI
    else if(matris[girisX-1][girisY]==1 && (girisX-1)<satir && -1<(girisX-1))
    {

        girisX--;
        matris[girisX][girisY]=2;
        ekle(&kok,girisX,girisY);
        yolBul( girisX,girisY,cikisX,cikisY,satir,sutun,matris);
    }


///CIKIS BULUNDUYSA
    if(cikisX==kok->x && cikisY==kok->y)
    {
        printf("\n");
        printf("Congratulations You Made It.\n");
        printf("\n");
        printf("Coordinates of the exit road:\n");
        labirentYaz(satir,sutun,matris);
        yedek=kok;
        int matrisYedek[satir][sutun];
        for(i=0;i<satir;i++)
            for(j=0;j<sutun;j++)
                matrisYedek[i][j]=0;

        for(i=0;kok!=NULL;i++){
            matrisYedek[kok->x][kok->y]=1;
            kok=kok->sonraki;
        }

        for(i=0; yedek!=NULL; i++)
        {
            printf("(%d,%d)\n",yedek->x,yedek->y);
            yedek=yedek->sonraki;
        }
        printf("\n");
        matris[girisX][girisY]=1;
        labirentYaz(satir,sutun,matrisYedek);
        exit(1);

    }
///CIKIS YOKSA
    else
    {
        if(kok->sonraki==NULL)
        {
            printf("There is no solution for the Value you enter.\n");
            exit(1);
        }
///GERI DONUS
        else
        {
            al(&kok);
            yolBul(kok->x,kok->y,cikisX,cikisY,satir,sutun,matris);
        }
    }
}

int main()
{

    int girisX,girisY,cikisX,cikisY,satir,sutun;
    srand(time(NULL));
    tekrar:
    printf("Enter the line number for the matrix:");
    scanf("%d",&satir);
    printf("Enter the column number for the matrix:");
    scanf("%d",&sutun);

    if(satir>30 && sutun>120){
        printf("Larger Screen Size Input Larger Matrix Re-enter..\n");
        goto tekrar;
    }


    int matris[satir][sutun];

    for(i=0; i<satir; i++)
        for(j=0; j<sutun; j++)
            matris[i][j]=rand()%2;


    printf("Your Maze:\n");
    system("cls");
    labirentYaz(satir,sutun,matris);
    printf("\n");
    giris:
    secim:
    printf("Enter the input coordinate.\n");

    printf("X:");
    scanf("%d",&girisX);

    printf("Y:");
    scanf("%d",& girisY);

    if(kontrol(girisX,girisY,satir,sutun)==0){
        printf("You cant enter the maze from middle.\nRe-Enter the coordinate.\n");
        goto secim;
    }

    secim1:
    printf("Enter the output coordinate.\n");

    printf("X:");
    scanf("%d",&cikisX);

    printf("Y:");
    scanf("%d",&cikisY);

    if(kontrol(cikisX,cikisX,satir,sutun)==0){
        printf("You cant get out the maze from middle.\nRe-Enter the coordinate.\n");
        goto secim1;
    }


    if(matris[girisX][girisY]==0 && matris[cikisX][cikisY]==0){
            system("cls");
        printf("Your input or output value is 0.\nRe-Enter the coordinate.\n");
        goto giris;
    }

    ekle(&kok,girisX,girisY);

    labirentYaz(satir,sutun,matris);

    yolBul(girisX,girisY,cikisX,cikisY,satir,sutun,matris);

    return 0;
}

void labirentYaz(int satir,int sutun,int matris[satir][sutun])
{   printf("  ");
    for(i=0;i<sutun;i++){
        printf("%d ",i);
    }
    printf("\n");

    for(i=0; i<satir; i++)
    {
        printf("%d ",i);
        for(j=0; j<sutun; j++)
        {
            printf("%d ",matris[i][j]);
        }
        printf("\n");
    }
}
int kontrol(int x,int y,int satir,int sutun)
{
    if(((x==0 && y<sutun && y>=0)||(y==0 && x<satir && x>=0)||(x==satir-1 && y<sutun && y>=0)||(y==sutun-1 && x<satir && x>=0)))
        return 1;
    else
        return 0;
}
