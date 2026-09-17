// Feyza ÖZBALTA
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

//ÇİFT YÖNLÜ BAĞLI LİSTE KULLANILDI.

typedef struct dugum {
	char ad[50];
	char soyad[50];
	char tel_no[15];
	struct dugum* sonraki;
	struct dugum* onceki;
}dugum;

//Fonksiyonlarda aynı değişkenleri tekrar tekrar vermeyelim diye bir struct daha tanımladım.
typedef struct {
	dugum* bas;
	dugum* son;
	int boyut;
}TelefonRehberi;

void olustur(TelefonRehberi* rehber);
void ekle(TelefonRehberi* rehber, char* ad, char* soyad, char* tel_no);
dugum* isme_gore_arama(TelefonRehberi* rehber, char* aranan_ad,char* aranan_soyad);
dugum* numaraya_gore_arama(TelefonRehberi* rehber, char* aranan_numara);
void sil(TelefonRehberi* rehber, char* aranan_ad,char* aranan_soyad);
void guncelle(TelefonRehberi* rehber, char* aranan_ad,char* aranan_soyad, char* yeni_tel_no);
void listele(TelefonRehberi* rehber);
void kucukHarfeDonustur(char* str, char* sonuc);
void bosalt(TelefonRehberi* rehber);

int main() {
	setlocale(LC_ALL, "Turkish");

	TelefonRehberi rehber;
	olustur(&rehber);

	while (1) {
		printf("TELEFON REHBERİ UYGULAMASI\n\n");
		printf("-MENÜ-\n");
		printf("1.Kullanıcı Ekleme\n");
		printf("2.Kullanıcı Silme\n");
		printf("3.Kullanıcı Güncelleme\n");
		printf("4.Kullanıcı Arama\n");
		printf("5.Kullanıcı Listeleme\n");
		printf("6.Çıkış\n\n");

		int secim;
		printf("Yapmak İstediğiniz İşlemi Seçiniz:\n");
		scanf("%d", &secim);

		if (secim == 1) {
			printf("-KULLANICI EKLEME MENÜSÜ-\n");
			char ad[50], soyad[50], tel_no[15];
			printf("Eklemek İstediğiniz Kişinin Adını Giriniz:\n");
			scanf("%s", ad);

			printf("Eklemek İstediğiniz Kişinin Soyadını Giriniz:\n");
			while (getchar() != '\n');  // Kişi soyadı kısmını boş bırakmak ister diye fgets ile aldım.Silme,güncelleme ve arama kısımlarını da aynı yaptım.
			fgets(soyad, 50, stdin);
			soyad[strcspn(soyad, "\n")] = '\0';

			printf("Eklemek İstediğiniz Kişinin Telefon Numarasını Boşluklu Olarak Giriniz:\n");
			fgets(tel_no, 15, stdin);
			tel_no[strcspn(tel_no, "\n")] = '\0';

			ekle(&rehber, ad, soyad, tel_no);
			printf("%s %s Başarıyla Eklendi!\n\n", ad, soyad);
		}

		else if (secim == 2) {
			char silinecek_ad[50],silinecek_soyad[50];
			printf("-KULLANICI SİLME MENÜSÜ-\n");
			printf("Silmek İstediğiniz Kullanıcının İsmini Giriniz:\n");
			scanf("%s", silinecek_ad);

			printf("Silmek İstediğiniz Kullanıcının Soyismini Giriniz:\n");
			while (getchar() != '\n');  // tamponu temizle
			fgets(silinecek_soyad, 50, stdin);
			silinecek_soyad[strcspn(silinecek_soyad, "\n")] = '\0';

			sil(&rehber, silinecek_ad,silinecek_soyad);
		}

		else if (secim == 3) {
			char guncellenecek_kisi[50], guncellenecek_numara[15],guncellenecek_soyad[50];
			printf("-KULLANICI GÜNCELLEME MENÜSÜ-\n");
			printf("Güncellemek İstediğiniz Kişinin Adını Giriniz:\n");
			scanf("%s", guncellenecek_kisi);

			printf("Güncellemek İstediğiniz Kişinin Soyadını Giriniz:\n");
			while (getchar() != '\n');  // tamponu temizle
			fgets(guncellenecek_soyad, 50, stdin);
			guncellenecek_soyad[strcspn(guncellenecek_soyad, "\n")] = '\0';

			dugum* bulunan = isme_gore_arama(&rehber, guncellenecek_kisi,guncellenecek_soyad);

			if (bulunan == NULL) {
				printf("Kişi Bulunamadı!\n\n");
			}
			else {
				printf("Yeni Numarayı Boşluklu Olarak Giriniz:\n");
				fgets(guncellenecek_numara, 15, stdin);
				guncellenecek_numara[strcspn(guncellenecek_numara, "\n")] = '\0';

				guncelle(&rehber, guncellenecek_kisi,guncellenecek_soyad, guncellenecek_numara);
			}
		}

		else if (secim == 4) {
			printf("-KULLANICI ARAMA MENÜSÜ-\n");
			printf("1.İsme Göre Ara\n");
			printf("2.Numaraya Göre Ara\n\n");
			int arama_secimi;
			printf("Yapmak İstediğiniz İşlemi Seçiniz:\n");
			scanf("%d", &arama_secimi);

			if (arama_secimi == 1) {
				char aranan_ad[50],aranan_soyad[50];
				printf("Aramak İstediğiniz Kişinin İsmini Giriniz:\n");
				scanf("%s", aranan_ad);

				printf("Aramak İstediğiniz Kişinin Soyismini Giriniz:\n");
				while (getchar() != '\n');  // tamponu temizle
				fgets(aranan_soyad, 50, stdin);
				aranan_soyad[strcspn(aranan_soyad, "\n")] = '\0';

				dugum* bulunan = isme_gore_arama(&rehber, aranan_ad,aranan_soyad);

				if (bulunan == NULL) {
					printf("Kişi Bulunamadı!\n\n");
				}

				else {
					printf("Kişi Bulundu: %s %s - %s\n\n", bulunan->ad, bulunan->soyad, bulunan->tel_no);
				}
			}

			else if (arama_secimi == 2) {
				char aranan_numara[15];
				printf("Aramak İstediğiniz Numarayı Boşluklu Olarak Giriniz:\n");
				while (getchar() != '\n');  // Tamponu temizler.
				fgets(aranan_numara, 15, stdin);
				aranan_numara[strcspn(aranan_numara, "\n")] = '\0';

				dugum* bulunan = numaraya_gore_arama(&rehber, aranan_numara);

				if (bulunan == NULL) {
					printf("Kişi Bulunamadı!\n\n");
				}

				else {
					printf("Kişi Bulundu: %s %s - %s\n\n", bulunan->ad, bulunan->soyad, bulunan->tel_no);
				}
			}
		}

		else if (secim==5) {
			printf("-Kişiler-\n");
			listele(&rehber);
		}
		
		else if (secim == 6) {
			printf("Programdan Çıkılıyor...\n");
			bosalt(&rehber);
			return 0;
		}

		else {
			printf("Geçersiz Seçim Yaptınız!\n\n");
		}
	}

}

void olustur(TelefonRehberi* rehber) {
	rehber->bas = NULL;
	rehber->son = NULL;
	rehber->boyut = 0;
}

void ekle(TelefonRehberi* rehber, char* ad,char* soyad,char* tel_no) {
	dugum* yeni = (dugum*)malloc(sizeof(dugum));

	strcpy(yeni->ad, ad);
	strcpy(yeni->soyad, soyad);
	strcpy(yeni->tel_no, tel_no);
	yeni->sonraki = NULL;
	yeni->onceki = NULL;

	if (rehber->bas == NULL) {
		rehber->bas = yeni;
		rehber->son = yeni;
	}
	else {
		yeni->onceki = rehber->son;
		rehber->son->sonraki = yeni;
		rehber->son = yeni;
	}
	rehber->boyut++;
}

dugum* isme_gore_arama(TelefonRehberi* rehber, char* aranan_ad,char* aranan_soyad) {
	dugum* gecici = rehber->bas;

	while (gecici != NULL) {
		char kucuk_ad[50], kucuk_soyad[50];
		char kucuk_aranan_ad[50], kucuk_aranan_soyad[50];

		kucukHarfeDonustur(gecici->ad, kucuk_ad);
		kucukHarfeDonustur(gecici->soyad, kucuk_soyad);
		kucukHarfeDonustur(aranan_ad, kucuk_aranan_ad);
		kucukHarfeDonustur(aranan_soyad, kucuk_aranan_soyad);

		if (strcmp(kucuk_ad, kucuk_aranan_ad) == 0 && strcmp(kucuk_soyad,kucuk_aranan_soyad)==0){
			return gecici;  //Eğer bulunduysa düğümü döndürür.
		}
		gecici = gecici->sonraki; //Sonrakine geçer.
	}
	return NULL; //Bulunamadı.
}

dugum* numaraya_gore_arama(TelefonRehberi* rehber, char* aranan_numara) {
	dugum* gecici = rehber->bas;

	while (gecici != NULL) {
		if (strcmp(gecici->tel_no, aranan_numara) == 0) {
			return gecici;
		}
		gecici = gecici->sonraki;
	}
	return NULL;
}

void sil(TelefonRehberi* rehber, char* aranan_ad,char* aranan_soyad) {
	dugum* silinecek = isme_gore_arama(rehber, aranan_ad,aranan_soyad);

	if (silinecek == NULL) {
		printf("Kişi Bulunamadı!");
		return;
	}

	else if (silinecek == rehber->bas) {
		rehber->bas = silinecek->sonraki; //Baş'ı bir ileri kaydırdım.
		if (rehber->bas != NULL) {
			rehber->bas->onceki = NULL; //Yeni başın önceki'si NULL olmalı.
		}
	}

	else if (silinecek == rehber->son) {
		rehber->son = silinecek->onceki;
		if (rehber->son != NULL) {
			rehber->son->sonraki = NULL;
		}
	}

	else {
		silinecek->onceki->sonraki = silinecek->sonraki;
		silinecek->sonraki->onceki = silinecek->onceki;
	}

	free(silinecek);
	rehber->boyut--;
	printf("%s Başarıyla Silindi!\n", aranan_ad);
}

void guncelle(TelefonRehberi* rehber, char* aranan_ad,char* aranan_soyad,char* yeni_tel_no) {
	dugum* bulunan = isme_gore_arama(rehber, aranan_ad,aranan_soyad);

	if (bulunan == NULL) {
		printf("Kişi Bulunamadı!\n");
		return;
	}

	else {
		strcpy(bulunan->tel_no,yeni_tel_no);
		printf("Telefon Numarası Başarıyla Güncellendi.\n");
	}
}

void listele(TelefonRehberi* rehber) {
	if (rehber->bas == NULL) {
		printf("Rehber Boş\n");
		return;
	}
	dugum* gecici = rehber->bas;
	while (gecici != NULL) {
		printf("%s %s - %s\n", gecici->ad, gecici->soyad, gecici->tel_no);
		gecici = gecici->sonraki;
	}
	
}

void kucukHarfeDonustur(char* str, char* sonuc) {
	int i;
	for (i = 0; str[i] != '\0'; i++) {
		sonuc[i] = tolower(str[i]);
	}
	sonuc[i] = '\0';
}

void bosalt(TelefonRehberi* rehber) {
	dugum* gecici = rehber->bas;
	dugum* sonraki;

	while (gecici != NULL) {
		sonraki = gecici->sonraki; //Sonraki dugumu kaybetmemek icin once kaydediyoruz.
		free(gecici);
		gecici = sonraki;
	}

	rehber->bas = NULL;
	rehber->son = NULL;
	rehber->boyut = 0;
}

/*ÇIKTI KISMI

TELEFON REHBERİ UYGULAMASI

- MENÜ -
1.Kullanıcı Ekleme
2.Kullanıcı Silme
3.Kullanıcı Güncelleme
4.Kullanıcı Arama
5.Kullanıcı Listeleme
6.Çıkış

Yapmak İstediğiniz İşlemi Seçiniz :
1
- KULLANICI EKLEME MENÜSÜ -
Eklemek İstediğiniz Kişinin Adını Giriniz :
Feyza
Eklemek İstediğiniz Kişinin Soyadını Giriniz :
Ozbalta
Eklemek İstediğiniz Kişinin Telefon Numarasını Boşluklu Olarak Giriniz :
0535 482 57 10
Feyza Ozbalta Başarıyla Eklendi!

----------------------------------------------------

TELEFON REHBERİ UYGULAMASI

- MENÜ -
1.Kullanıcı Ekleme
2.Kullanıcı Silme
3.Kullanıcı Güncelleme
4.Kullanıcı Arama
5.Kullanıcı Listeleme
6.Çıkış

Yapmak İstediğiniz İşlemi Seçiniz :
2
- KULLANICI SİLME MENÜSÜ -
Silmek İstediğiniz Kullanıcının İsmini Giriniz :
Feyza
Silmek İstediğiniz Kullanıcının Soyismini Giriniz :
Ozbalta
Feyza Başarıyla Silindi!

----------------------------------------------------

TELEFON REHBERİ UYGULAMASI

-MENÜ-
1.Kullanıcı Ekleme
2.Kullanıcı Silme
3.Kullanıcı Güncelleme
4.Kullanıcı Arama
5.Kullanıcı Listeleme
6.Çıkış

Yapmak İstediğiniz İşlemi Seçiniz:
3
-KULLANICI GÜNCELLEME MENÜSÜ-
Güncellemek İstediğiniz Kişinin Adını Giriniz:
Feyza
Güncellemek İstediğiniz Kişinin Soyadını Giriniz:
Ozbalta
Yeni Numarayı Boşluklu Olarak Giriniz:
0535 492 57 10
Telefon Numarası Başarıyla Güncellendi.

----------------------------------------------------

TELEFON REHBERİ UYGULAMASI

-MENÜ-
1.Kullanıcı Ekleme
2.Kullanıcı Silme
3.Kullanıcı Güncelleme
4.Kullanıcı Arama
5.Kullanıcı Listeleme
6.Çıkış

Yapmak İstediğiniz İşlemi Seçiniz:
4
-KULLANICI ARAMA MENÜSÜ-
1.İsme Göre Ara
2.Numaraya Göre Ara

Yapmak İstediğiniz İşlemi Seçiniz:
1
Aramak İstediğiniz Kişinin İsmini Giriniz:
Feyza
Aramak İstediğiniz Kişinin Soyismini Giriniz:
Ozbalta
Kişi Bulundu: Feyza Ozbalta - 0535 492 57 10

----------------------------------------------------

-MENÜ-
1.Kullanıcı Ekleme
2.Kullanıcı Silme
3.Kullanıcı Güncelleme
4.Kullanıcı Arama
5.Kullanıcı Listeleme
6.Çıkış

Yapmak İstediğiniz İşlemi Seçiniz:
4
-KULLANICI ARAMA MENÜSÜ-
1.İsme Göre Ara
2.Numaraya Göre Ara

Yapmak İstediğiniz İşlemi Seçiniz:
2
Aramak İstediğiniz Numarayı Boşluklu Olarak Giriniz:
0535 492 57 10
Kişi Bulundu: Feyza Ozbalta - 0535 492 57 10

-------------------------------------------------------

TELEFON REHBERİ UYGULAMASI

-MENÜ-
1.Kullanıcı Ekleme
2.Kullanıcı Silme
3.Kullanıcı Güncelleme
4.Kullanıcı Arama
5.Kullanıcı Listeleme
6.Çıkış

Yapmak İstediğiniz İşlemi Seçiniz:
5
-Kişiler-
Feyza Ozbalta - 0535 492 57 10

-------------------------------------------------------

TELEFON REHBERİ UYGULAMASI

-MENÜ-
1.Kullanıcı Ekleme
2.Kullanıcı Silme
3.Kullanıcı Güncelleme
4.Kullanıcı Arama
5.Kullanıcı Listeleme
6.Çıkış

Yapmak İstediğiniz İşlemi Seçiniz:
6
Programdan Çıkılıyor...

*/