# Telefon Rehberi Uygulaması

C dilinde, çift yönlü bağlı liste (doubly linked list) kullanılarak geliştirilmiş konsol tabanlı bir telefon rehberi uygulaması.

## Özellikler

- **Kişi Ekleme** — Ad, soyad ve telefon numarası bilgileriyle yeni kayıt oluşturma
- **Kişi Silme** — Ad-soyad ile arayıp kaydı listeden kaldırma
- **Kişi Güncelleme** — Mevcut bir kaydın telefon numarasını değiştirme
- **Kişi Arama** — Ada göre veya telefon numarasına göre arama (büyük/küçük harf duyarsız)
- **Kişi Listeleme** — Kayıtlı tüm kişileri sırayla listeleme

## Kullanılan Yapılar ve Kavramlar

- Çift yönlü bağlı liste (`onceki` / `sonraki` işaretçileri)
- Liste durumunu (baş, son, boyut) tek bir `TelefonRehberi` yapısında toplama
- `malloc` / `free` ile dinamik bellek yönetimi; program kapanırken tüm düğümlerin serbest bırakılması
- `fgets` ile boşluk içeren girdilerin (soyad, telefon numarası) doğru okunması ve giriş tamponunun yönetimi
- Harf duyarsız karşılaştırma için özel küçük harfe dönüştürme fonksiyonu

## Nasıl Çalıştırılır

```bash
gcc -o rehber rehber.c
./rehber
```

Windows'ta Visual Studio ile de doğrudan derlenip çalıştırılabilir.

## Örnek Kullanım

```
TELEFON REHBERİ UYGULAMASI

-MENÜ-
1.Kullanıcı Ekleme
2.Kullanıcı Silme
3.Kullanıcı Güncelleme
4.Kullanıcı Arama
5.Kullanıcı Listeleme
6.Çıkış

Yapmak İstediğiniz İşlemi Seçiniz:
1
-KULLANICI EKLEME MENÜSÜ-
Eklemek İstediğiniz Kişinin Adını Giriniz:
Feyza
Eklemek İstediğiniz Kişinin Soyadını Giriniz:
Ozbalta
Eklemek İstediğiniz Kişinin Telefon Numarasını Boşluklu Olarak Giriniz:
0535 482 57 10
Feyza Ozbalta Başarıyla Eklendi!
```

## Notlar

Bu proje, veri yapıları dersinde edinilen bağlı liste bilgisinin pratiğe dökülmesi amacıyla geliştirilmiştir.
