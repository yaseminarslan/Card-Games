// Yasemin Arslan
// 180401032
// Yapisal Programlama Uzaktan Egitim Proje Odevi

//        Kartlarin onem siralamasi:
//             Kupa > Karo > Maca > Sinek 
//             As > Papaz > Kiz > Vale

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 52 adet iskambil karti tanimlanir.
#define CARD 52

// kartlar icin struct olusturulur.
// cinsDeger ve noDeger integerlari kartlari siralayabilmek icin deger vermek amaclidir.
struct KART {
    char *cins;
    int cinsDeger;
    char *no;
    int noDeger;
};

// oyuncular icin struct olusturulur.
struct OYUNCU {
    // oyuncunun 4 kartini tutacak.
    struct KART kartlar[4];
    int puan;
};

// desteyi olusturan bir fonksiyon.
void desteYap(struct KART *deste, char *cins[], char *no[]){
    int i;
    for(i = 0; i < CARD; ++i){
        deste[i].no = no[i % 13];
        deste[i].cins = cins[i / 13];
        deste[i].noDeger = i % 13;
        deste[i].cinsDeger = i / 13;
        
    }
}

// oyunculara toplam 8 adet iskambil kagidi dagitimak icin bir fonksiyon.
void dagit(struct KART *deste, struct OYUNCU *oyuncu){
    for(int i = 0; i < 8; ++i){
        oyuncu[i % 2].kartlar[(int)(i/2)].cins = deste[i].cins;
        oyuncu[i % 2].kartlar[(int)(i/2)].no = deste[i].no;
        oyuncu[i % 2].kartlar[(int)(i/2)].cinsDeger = deste[i].cinsDeger;
        oyuncu[i % 2].kartlar[(int)(i/2)].noDeger = deste[i].noDeger;
    }
}

// oyunculara dagitilan kartlari ekrana bastirmak icin bir fonksiyon.
void printKartlar(struct OYUNCU *oyuncu) {
    for(int j = 0; j < 2; j++){
        for(int i = 0; i <4; i++){
            printf("Oyuncu %d : %s %s \n", j+1, oyuncu[j].kartlar[i].cins, oyuncu[j].kartlar[i].no);
        }
    }
}

// oyuncularin puanlarini yazdirmak icin bir fonksiyon.
void puanYazdir(int i, struct OYUNCU *oyuncu) {
    printf("%d el sonu oyuncu puanlari: %d %d \n", i + 1,  oyuncu[0].puan, oyuncu[1].puan);
}

// kartlari karistirmak icin bir fonksiyon. ayni karttan ayni elde bir daha gelmeyecegine dair emin olunuyor.
void karistir(struct KART *deste){
    struct KART temp;
    srand(time(NULL));
    for(int i = 0; i < CARD; ++i){
        int j = rand() % CARD;
        temp = deste[i];
        deste[i] = deste[j];
        deste[j] = temp;
    }
}

// oyuncularin once kart cinsleri *Kupa, Karo, Maca, Sinek* karsilatiriliyor. 
void karsilastir(struct OYUNCU *oyuncu) {
    for(int i = 0; i < 4; i++) {
        if(oyuncu[0].kartlar[i].cinsDeger < oyuncu[1].kartlar[i].cinsDeger) {
            oyuncu[0].puan++;
        }
        else if (oyuncu[0].kartlar[i].cinsDeger > oyuncu[1].kartlar[i].cinsDeger) {
            oyuncu[1].puan++;
        }
        else {
            // oyuncular ayni kart cinsine sahipse bu sefer kartin numarasina *no* bakiliyor.
            if(oyuncu[0].kartlar[i].noDeger < oyuncu[1].kartlar[i].noDeger) {
                oyuncu[0].puan++;
            }
            else {
                oyuncu[1].puan++;
            }
        }
    }
}

// oyunun sonunda kazanani yazdiran fonksiyon.
void kazananiYazdir(struct OYUNCU *oyuncu) {
    if(oyuncu[0].puan > oyuncu[1].puan){
        printf("%d puanla 1. oyuncu kazandi. \n", oyuncu[0].puan);
    }
    else if(oyuncu[0].puan < oyuncu[1].puan){
        printf("%d puanla 2. oyuncu kazandi.\n", oyuncu[1].puan);
    }
    else {
        printf("%d puanla berabere bitti.\n", oyuncu[1].puan);   
    }
}

// mainin icinde loopda oyunu oynatmak icin tum fonksiyonlari cagiran oyun fonksiyonu.
void oyun(struct KART *deste, struct OYUNCU *oyuncu){
    oyuncu[0].puan = 0;
    oyuncu[1].puan = 0;
    for(int i = 0; i < 10; i++){
        karistir(deste);
        dagit(deste, oyuncu);
        printKartlar(oyuncu);
        karsilastir(oyuncu);
        puanYazdir(i, oyuncu);
    }
    kazananiYazdir(oyuncu);
}


int main(void){
    int i;
    struct KART deste[CARD];
// pointer dizisi
    char *no[] = {  "As", "Papaz", "Kiz", "Vale", "On", "Dokuz", "Sekiz", "Yedi",
     "Alti", "Bes", "Dort", "Uc", "Iki"};

    // char *no = "papaz";

    char *cins[] = {"Kupa", "Karo", "Maca", "Sinek"};

    struct OYUNCU oyuncu[2];
    desteYap(deste, cins, no);
    // loopa almak icin bir kere oyunu oynatip devam edip etmeyecegini soruyoruz.
    oyun(deste, oyuncu);  
    printf("Tekrar oynamak icin t veya T tusuna,  cikmak icin q veya Q tusuna basiniz :\n");
    
    // kullanicinin tekrar oynamak istemesi karakter 't' veya 'T' ile saglanacaktir.
    // kullanicinin cikmak istemesi ise karakter 'q' veya 'Q' ile saglanacaktir.
    // kullanici baska bir karakter girerse hatayla karsilasip secim yapmasi istenir.
    char c = 't';
    while(c == 't'){
        char c = 't';
        c = getchar();
        if(c == 't' || c == 'T'){
        oyun(deste, oyuncu); 
        }
        else if( c == 'q' || c == 'Q'){
            break;
        }
        printf("Tekrar oynamak icin t veya T tusuna,  cikmak icin q veya Q tusuna basiniz :\n");
        c = getchar();
    }

// kullanicinin istegi uzerine oyun sonlandirilir.
    printf("Oyun sonlandi.\n");

    return 0;
}

