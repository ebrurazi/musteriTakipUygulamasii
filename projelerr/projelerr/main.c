#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>

//Global değişkenler olarak ad, soyad, tel ve adres tanımlandı
char ad[20];
char soyad[20];
char tel[20];
char adres[20];

FILE *dosya;
FILE *gecici;
//Fonksiyonları burada tanımlandı
void ekle(void);
void listele(void);
void ara(void);
void sil(void);
void yedekle(void);
void guncelle(char *);

int main(void){
    int secim=1;
    printf("********************** MUSTERİ TAKİP UYGULAMASI **********************\n");
    printf("\t\t\t\t\t\tHOŞ GELDİNİZ");
    //Kullanıcı 0 seçmediği sürece yani çıkış yapmadığı sürece while dongüsü devam eder
    while (secim!=0) {
        printf("\n1 - Ekle\n");
        printf("2 - Listele\n");
        printf("3 - Ara\n");
        printf("4 - Sil\n");
        printf("0 - Çıkış\n");
        printf("Seçiminiz : ");
        scanf("%d",&secim);
        
        if (secim==1)
            ekle();
        else if(secim==2)
            listele();
        else if(secim==3)
            ara();
        else if(secim==4)
            sil();
        else if(secim==0)
            exit(0);
        else
            printf("Hatalı seçim yaptınız!!\n");
            
    }
    printf("\n");
    return 0;
}

void ekle(void){
    //Kullanıcıdan alınan müşteri bilgileri txt dosyasınna kaydedilir
    printf("Kayıt edilecek musteri bilgilerini giriniz : \n");
    printf("Ad     :");
    scanf("%s",ad);
    printf("Soyad  :");
    scanf("%s",soyad);
    printf("Tel    :");
    scanf("%s",tel);
    printf("Adres  :");
    scanf("%s",adres);
    
    if ((dosya = fopen("/Users/ebrurazi/Desktop/musKayit.txt ","a")) != NULL) {
        fprintf(dosya,"%s\t%s\t%s\t%s\n",ad,soyad,tel,adres);
    }
    printf("Kayıt işlemi başarışı!!\n");
    fclose(dosya);
}
void listele(void){
    //Kayıt edilen müşteri bilgilerini listeler
    printf("Kayıtlı Müşteri Bilgileri\n");
    printf("\n**************************** \n");
    printf("Ad\t\tSoyad\tTelefon\t\tAdres\n");
    
    
    if ((dosya = fopen("/Users/ebrurazi/Desktop/musKayit.txt ","r")) != NULL) {
        strcpy(ad,"");
        strcpy(soyad,"");
        strcpy(tel,"");
        strcpy(adres,"");
        
        while (!feof(dosya)) {
            fscanf(dosya,"%s\t%s\t%s\t%s\n",ad,soyad,tel,adres);
            printf("%s\t%s\t%s\t%s\n",ad,soyad,tel,adres);
        }
        printf("\n**************************** \n");
    }
    printf("Listeleme işlemi başarılı \n");
    fclose(dosya);
    
}
void ara(void){
    //Kullanıcın girdiği ismin kayıtlı olup olmadığını kontrol eder
    char isim[20];
    int sonuc=0;
    
    printf("Aradığınız müşterinin ismi : ");
    scanf("%s",isim);
    
    printf("\nAranan Müşteri Bilgileri\n");
    printf("\n**************************** \n");
    printf("Ad\tSoyad\tTelefon\t\tAdres\n");
    
    
    if ((dosya = fopen("/Users/ebrurazi/Desktop/musKayit.txt ","r")) != NULL) {
        while (!feof(dosya)) {
            fscanf(dosya,"%s\t%s\t%s\t%s\n",ad,soyad,tel,adres);
            if(strcmp(isim,ad)==0){
                printf("%s\t%s\t%s\t%s\n",ad,soyad,tel,adres);
                fclose(dosya);
                sonuc=1;
        
                break;
            }
           
        }
        printf("\n**************************** \n");
    }
    fclose(dosya);
    if (sonuc==0) {
        printf("%s isimli musteri listede yok\n",isim);
    }
    
}
void sil(void){
    //Kullanıcın silmek istediği ismi txt dosyasından siler
    char isim[20];
    int sonuc=0;
    
    printf("Silmek istediğiniz müşterinin ismi : ");
    scanf("%s",isim);
    
    
    if ((dosya = fopen("/Users/ebrurazi/Desktop/musKayit.txt ","r")) != NULL) {
        while (!feof(dosya)) {
            fscanf(dosya,"%s\t%s\t%s\t%s\n",ad,soyad,tel,adres);
            if(strcmp(isim,ad)==0){
                yedekle();
                guncelle(isim);
                fclose(dosya);
                sonuc=1;
        
                break;
            }
           
        }
        printf("\n**************************** \n");
    }
    fclose(dosya);
    if (sonuc==0) {
        printf("%s isimli musteri listede yok\n",isim);
    }
    else
        printf("Silme işlemi başarılı!!\n");
}

//Silmek istediğimiz ismi yedek dosyaya atıp ondan sonra silme işlemi yapılır
void yedekle(void){
    if ((gecici = fopen("/Users/ebrurazi/Desktop/yedekKayit.txt ","w")) != NULL) {
        if ((dosya = fopen("/Users/ebrurazi/Desktop/musKayit.txt ","r")) != NULL){
            while (!feof(dosya)) {
                fscanf(dosya,"%s\t%s\t%s\t%s\n",ad,soyad,tel,adres);
                fprintf(gecici,"%s\t%s\t%s\t%s\n",ad,soyad,tel,adres);
            }
        }
    }
    remove("/Users/ebrurazi/Desktop/musKayit.txt");
    fclose(gecici);
    fclose(dosya);

}
void guncelle(char *ptrIsim){
    
    if ((dosya = fopen("/Users/ebrurazi/Desktop/musKayit.txt ","w")) != NULL) {
        if ((gecici = fopen("/Users/ebrurazi/Desktop/yedekKayit.txt ","r")) != NULL){
            while (!feof(gecici)) {
                fscanf(gecici,"%s\t%s\t%s\t%s\n",ad,soyad,tel,adres);
                if (strcmp(ptrIsim,ad) == 0)
                    continue;
                    fprintf(dosya ,"%s\t%s\t%s\t%s\n",ad,soyad,tel,adres);
                }
        }
    }
    remove("/Users/ebrurazi/Desktop/yedekKayit.txt");
    fclose(gecici);
    fclose(dosya);
}

