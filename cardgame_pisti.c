/* 
 * Yasemin Arslan
 * 180401032
 * Yapısal Final Proje
 * 
 * Description: // Pisti Oyunu
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 52 adet iskambil karti tanimlanir.
#define CARD 52
#define OYUNCU_SAYISI 2
// oyuncu sayisini degistirerek asagiya ekleme yapildiginda 2den fazla kisiyle oynanabilir* 
// (((52-4)/4)/oyuncu_sayisi) sebebiyle oyuncu sayisinin 12'ye bolunmesi lazim**

struct KART {
    char *cins;
    int cinsDeger;
    char *no;
    int noDeger;
};

// oyuncular icin struct olusturulur.
struct OYUNCU {
    int id;
    char *isim;
    // oyuncunun 4 kartini tutacak.
    struct KART eldekiKartlar[4];
    struct KART kazanilanKartlar[CARD];
    // kazanilan kartlarda nereye eklenecegini gosterecek.
    int eldekiKartSayisi;
    int kazanilanKartSayisi;
    int pistiSayisi;
    int puan;

};

struct PISTI {
    struct KART atilanKartlar[8];
    struct KART yerdekiKartlar[CARD];
    // son kart icin
    int yerdekiKartSayisi;
    int sonKazanan;
};

// kart sayisini tutar. 
int k = 0;

// asagida fonksiyonlarda esitleme kisimlari uzun ve kafa karistirici oldugu icin bu fonksiyonu yazdim. 
// structlari daha kolay bir sekilde kopyalamamizi sagliyor.
void kartKopyala(struct KART *dst, struct KART *src){
    dst->cins = src->cins;
    dst->cinsDeger = src->cinsDeger;
    dst->no = src->no;
    dst->noDeger = src->noDeger;

}


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

// kartlari dagitiyoruz.
void kartDagit(struct KART *deste, struct OYUNCU *oyuncu){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < OYUNCU_SAYISI; j++ ){
            kartKopyala(&oyuncu[j].eldekiKartlar[i], &deste[k]);
            // oyuncu[j].eldekiKartlar[i].cins = deste[k].cins;
            // oyuncu[j].eldekiKartlar[i].cinsDeger = deste[k].cinsDeger;
            // oyuncu[j].eldekiKartlar[i].no = deste[k].no;
            // oyuncu[j].eldekiKartlar[i].noDeger = deste[k].noDeger;
            k++;
            oyuncu[j].eldekiKartSayisi++;
        }
    }
}

// pisti bir eleman oldugu icin ok operatoru ile ulasilir.
void ilkEl(struct KART *deste, struct PISTI *pisti){
    // ilk el oldugu icin sifirla.
    pisti->yerdekiKartSayisi = 0;
    for(int i = 0; i < 4; i++){
        kartKopyala(&pisti->yerdekiKartlar[i] ,&deste[k]);
        // pisti->yerdekiKartlar[i].cins = deste[k].cins;
        // pisti->yerdekiKartlar[i].cinsDeger = deste[k].cinsDeger;
        // pisti->yerdekiKartlar[i].no = deste[k].no;
        // pisti->yerdekiKartlar[i].noDeger = deste[k].noDeger;
        k++;
        pisti->yerdekiKartSayisi++;
    }
}

// kartlari ekrana yazdir.
void kartlariYazdir(struct PISTI *pisti, struct OYUNCU *oyuncu){
    printf("\n\n=================================\n");
    printf("|    YERDEKI    |    YERDEKI    |\n");
    printf("|    KARTLAR    |    SON KART   |\n");
    printf("---------------------------------\n");
    for(int i = 0; i < pisti->yerdekiKartSayisi; i++){
        printf("| %s\t%s\t", pisti->yerdekiKartlar[i].cins, pisti->yerdekiKartlar[i].no);
        if(i == 0){
            printf("| %s\t%s\t|", pisti->yerdekiKartlar[pisti->yerdekiKartSayisi -1].cins, pisti->yerdekiKartlar[pisti->yerdekiKartSayisi -1].no);
        }
        else{
            printf("| \t\t|");
        }
        printf("\n");
    }       
    printf("\n---------------------------------\n");


    // for(int i = 0; i < OYUNCU_SAYISI; i++){
        printf("%s elindeki kartlar : \n", oyuncu[0].isim);

        for(int j = 0; j < oyuncu[0].eldekiKartSayisi; j++){
            printf("%s %s, ", oyuncu[0].eldekiKartlar[j].cins, oyuncu[0].eldekiKartlar[j].no);
        }
        printf("\n");
    // }
}

// kartAt fonksiyonunda pisti olup olmama durumu ve puanlamaya bakiyoruz.
void kartAt(struct PISTI *pisti, struct OYUNCU *oyuncu, int kartno){
    if((oyuncu->eldekiKartlar[kartno].noDeger == pisti->yerdekiKartlar[pisti->yerdekiKartSayisi-1].noDeger) || ((oyuncu->eldekiKartlar[kartno].noDeger == 3) && (pisti->yerdekiKartSayisi != 0))){
        pisti->sonKazanan = oyuncu->id;
        if((pisti->yerdekiKartSayisi != 1)|| (oyuncu->eldekiKartlar[kartno].noDeger != pisti->yerdekiKartlar[pisti->yerdekiKartSayisi-1].noDeger)){
            printf("\n---> %s %s %s atarak yerdeki kagitlari topladi. Yerde %s %s vardı\n", oyuncu->isim, oyuncu->eldekiKartlar[kartno].cins, oyuncu->eldekiKartlar[kartno].no, pisti->yerdekiKartlar[pisti->yerdekiKartSayisi-1].cins, pisti->yerdekiKartlar[pisti->yerdekiKartSayisi-1].no);
            // pisti olmama durumu
            for(int i = 0; i < pisti->yerdekiKartSayisi; i++){
                kartKopyala(&oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi], &pisti->yerdekiKartlar[i] );
                // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].cins = pisti->yerdekiKartlar[i].cins;
                // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].cinsDeger = pisti->yerdekiKartlar[i].cinsDeger;
                // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].no = pisti->yerdekiKartlar[i].no;
                // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].noDeger = pisti->yerdekiKartlar[i].noDeger;
                oyuncu->kazanilanKartSayisi++;
            }
            kartKopyala(&oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi], &oyuncu->eldekiKartlar[kartno]);
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].cins = oyuncu->eldekiKartlar[kartno].cins;
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].cinsDeger = oyuncu->eldekiKartlar[kartno].cinsDeger;
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].no = oyuncu->eldekiKartlar[kartno].no;
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].noDeger = oyuncu->eldekiKartlar[kartno].noDeger;

            oyuncu->kazanilanKartSayisi++;
            pisti->yerdekiKartSayisi = 0;
        }
        else {
            // pisti olma durumu
            printf("\n---> %s %s %s atarak Pişti Yaptı, Yerde %s %s vardı\n", oyuncu->isim,  oyuncu->eldekiKartlar[kartno].cins, oyuncu->eldekiKartlar[kartno].no, pisti->yerdekiKartlar[0].cins, pisti->yerdekiKartlar[0].no);
            kartKopyala(&oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi], &pisti->yerdekiKartlar[0]);
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].cins = pisti->yerdekiKartlar[0].cins;
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].cinsDeger = pisti->yerdekiKartlar[0].cinsDeger;
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].no = pisti->yerdekiKartlar[0].no;
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].noDeger = pisti->yerdekiKartlar[0].noDeger;
            // vale durumu.
            if(pisti->yerdekiKartlar[0].noDeger == 3){
                oyuncu->pistiSayisi+=2;
            }
            else{
                oyuncu->pistiSayisi++;
            }

            oyuncu->kazanilanKartSayisi++;

            kartKopyala(&oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi], &oyuncu->eldekiKartlar[kartno]);
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].cins = oyuncu->eldekiKartlar[kartno].cins;
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].cinsDeger = oyuncu->eldekiKartlar[kartno].cinsDeger;
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].no = oyuncu->eldekiKartlar[kartno].no;
            // oyuncu->kazanilanKartlar[oyuncu->kazanilanKartSayisi].noDeger = oyuncu->eldekiKartlar[kartno].noDeger;

            oyuncu->kazanilanKartSayisi++;

            pisti->yerdekiKartSayisi = 0;
        }
    }
    else{
        kartKopyala(&pisti->yerdekiKartlar[pisti->yerdekiKartSayisi] ,&oyuncu->eldekiKartlar[kartno]);
        // pisti->yerdekiKartlar[pisti->yerdekiKartSayisi].cins = oyuncu->eldekiKartlar[kartno].cins;
        // pisti->yerdekiKartlar[pisti->yerdekiKartSayisi].cinsDeger = oyuncu->eldekiKartlar[kartno].cinsDeger;
        // pisti->yerdekiKartlar[pisti->yerdekiKartSayisi].no = oyuncu->eldekiKartlar[kartno].no;
        // pisti->yerdekiKartlar[pisti->yerdekiKartSayisi].noDeger = oyuncu->eldekiKartlar[kartno].noDeger;

        pisti->yerdekiKartSayisi++;
    }
    if(oyuncu->eldekiKartSayisi > 0){
        kartKopyala(&oyuncu->eldekiKartlar[kartno] ,&oyuncu->eldekiKartlar[oyuncu->eldekiKartSayisi-1]);
        // oyuncu->eldekiKartlar[kartno].cins = oyuncu->eldekiKartlar[oyuncu->eldekiKartSayisi-1].cins;
        // oyuncu->eldekiKartlar[kartno].cinsDeger = oyuncu->eldekiKartlar[oyuncu->eldekiKartSayisi-1].cinsDeger;
        // oyuncu->eldekiKartlar[kartno].no = oyuncu->eldekiKartlar[oyuncu->eldekiKartSayisi-1].no;
        // oyuncu->eldekiKartlar[kartno].noDeger = oyuncu->eldekiKartlar[oyuncu->eldekiKartSayisi-1].noDeger;
        oyuncu->eldekiKartSayisi--;
    } 
}

// bilgisayara kart sectiriyoruz.
int bilgisayarKartSec(struct PISTI *pisti, struct OYUNCU *oyuncu){
    for(int i = 0; i < oyuncu->eldekiKartSayisi; i++){
        if(pisti->yerdekiKartlar[pisti->yerdekiKartSayisi-1].noDeger == oyuncu->eldekiKartlar[i].noDeger){
            return i;
        }
    }
    // elimizde yok o yuzden 0. kartini at.
    return 0;
}

// Puan ekleyip Kart sayisi ve pisti sayisini, kimin kac kart aldigini ve kazanani ekrana yazdiriyoruz.
void puanSayma(struct OYUNCU *oyuncu) {
    for(int i = 0; i < OYUNCU_SAYISI; i++){
        int puan = 0;
        for(int j = 0; j < oyuncu[i].kazanilanKartSayisi; j++){
            if((oyuncu[i].kazanilanKartlar[j].noDeger == 0) || (oyuncu[i].kazanilanKartlar[j].noDeger == 3)){
                puan++;
            }
            else if((oyuncu[i].kazanilanKartlar[j].noDeger == 4) && (oyuncu[i].kazanilanKartlar[j].cinsDeger == 1)) {
                puan = puan + 3;
            }
            else if((oyuncu[i].kazanilanKartlar[j].noDeger == 12) && (oyuncu[i].kazanilanKartlar[j].cinsDeger == 2)) {
                puan = puan + 2;
            }

        }
        oyuncu[i].puan = puan + oyuncu[i].pistiSayisi * 10;
    }
    printf("Kart sayilari : \n");
    for(int i = 0; i < OYUNCU_SAYISI; i++){
        printf("%s : %d\n", oyuncu[i].isim, oyuncu[i].kazanilanKartSayisi);
        }
    
    printf("Pisti sayilari : \n");
    for(int i = 0; i < OYUNCU_SAYISI; i++){
        printf("%s : %d\n", oyuncu[i].isim, oyuncu[i].pistiSayisi);
        }
    int max = 0;
    int oid = OYUNCU_SAYISI;

    for(int i = 0; i < OYUNCU_SAYISI; i++){
        if(oyuncu[i].kazanilanKartSayisi > max){
            oid = oyuncu[i].id;
        }
    }
    oyuncu[oid].puan += 3;

    printf("----------\n");
    printf("%s %d puan aldi\n", oyuncu[0].isim, oyuncu[0].puan);
    printf("%s %d puan aldi\n", oyuncu[1].isim, oyuncu[1].puan);
    if(oyuncu[0].puan > oyuncu[1].puan){
        printf("Kazanan %s\n", oyuncu[0].isim);
    }
    else if(oyuncu[1].puan > oyuncu[0].puan){
        printf("Kazanan %s\n", oyuncu[1].isim);
    }
    else{
        printf("Berabere bitti.\n");
    }

}

// oyuncularin kartlarini ekrana yazdiriyoruz.
void oyuncuKartlariYazdir(struct OYUNCU *oyuncu){
    for(int i = 0; i < OYUNCU_SAYISI; i++){
        printf("----------\n");
        printf("%s 'in kazandigi kartlar: \n", oyuncu[i].isim);
        for(int j = 0; j < oyuncu[i].kazanilanKartSayisi; j++){
        printf("%s %s\n", oyuncu[i].kazanilanKartlar[j].cins, oyuncu[i].kazanilanKartlar[j].no);
        }
    }
}


void sonEliAktar(struct PISTI *pisti, struct OYUNCU *oyuncu){
    for(int i = 0; i < pisti->yerdekiKartSayisi; i++){
        kartKopyala(&oyuncu[pisti->sonKazanan].kazanilanKartlar[oyuncu[pisti->sonKazanan].kazanilanKartSayisi], &pisti->yerdekiKartlar[i]);
        // oyuncu[pisti->sonKazanan].kazanilanKartlar[oyuncu[pisti->sonKazanan].kazanilanKartSayisi].cins = pisti->yerdekiKartlar[i].cins;
        // oyuncu[pisti->sonKazanan].kazanilanKartlar[oyuncu[pisti->sonKazanan].kazanilanKartSayisi].cinsDeger = pisti->yerdekiKartlar[i].cinsDeger;
        // oyuncu[pisti->sonKazanan].kazanilanKartlar[oyuncu[pisti->sonKazanan].kazanilanKartSayisi].no = pisti->yerdekiKartlar[i].no;
        // oyuncu[pisti->sonKazanan].kazanilanKartlar[oyuncu[pisti->sonKazanan].kazanilanKartSayisi].noDeger = pisti->yerdekiKartlar[i].noDeger;
        // oyuncu[pisti->sonKazanan].kazanilanKartSayisi++;
    }   
}

int oyuncuKartSec(struct OYUNCU *oyuncu){
    int sec = 0;
    while((sec < 1) || (sec > oyuncu->eldekiKartSayisi)){
        for(int i = 0; i < oyuncu->eldekiKartSayisi; i++){
            printf("[%d] %s %s   ", i+1, oyuncu->eldekiKartlar[i].cins, oyuncu->eldekiKartlar[i].no);   
        }
        printf("\n kart seciniz: ");
        scanf("%d", &sec);
    }
        return sec-1;
}






int main(void){
    int i;
    struct KART deste[CARD];
    // pointer dizisi
    char *no[] = {  "As", "Papaz", "Kiz", "Vale", "10", "9", "8", "7",
     "6", "5", "4", "3", "2"};

    char *cins[] = {"Kupa", "Karo", "Maca", "Sinek"};

    struct OYUNCU oyuncu[OYUNCU_SAYISI];
    oyuncu[0].isim = "Yasemin";
    oyuncu[1].isim = "Bilgisayar";
    // oyuncu[2].isim = "Ayse";
    // oyuncu[3].isim = "Fatma";
    // daha fazla kisiyle oynamak istersek diye*

    for(int i = 0; i < OYUNCU_SAYISI; i++){
        oyuncu[i].eldekiKartSayisi = 0;
        oyuncu[i].puan = 0;
        oyuncu[i].kazanilanKartSayisi = 0;
        oyuncu[i].pistiSayisi = 0;
        oyuncu[i].id = i;
    }
    desteYap(deste, cins, no);
    karistir(deste);

    int siradakiKart = 0;
    struct PISTI pisti;
    pisti.sonKazanan = OYUNCU_SAYISI;

    // pistinin adresini gonderdik
    ilkEl(deste, &pisti);
    for(int elSayisi = 0; elSayisi < (int)(((CARD-4)/4)/OYUNCU_SAYISI); elSayisi++){
        printf("## %d. el \n", elSayisi + 1);
        kartDagit(deste, oyuncu);
        kartlariYazdir(&pisti, oyuncu);


        for(int i = 0; i < 4; i++){
            for(int j = 0; j < OYUNCU_SAYISI; j++){
                if(j == 1){
                    siradakiKart = bilgisayarKartSec(&pisti, &oyuncu[1]);
                }
                else{
                    siradakiKart = oyuncuKartSec(&oyuncu[j]);
                }
                kartAt(&pisti, &oyuncu[j], siradakiKart);
                kartlariYazdir(&pisti, oyuncu);
            }
        }
    }
    sonEliAktar(&pisti, oyuncu);
    oyuncuKartlariYazdir(oyuncu);
    puanSayma(oyuncu);
}

