#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void getcompanytype();
void getinfo();
void getlogo();
void subesema(int);
void vergi(double *);
void ticaret();
void turizm();

char *firmaAD; // DİNAMİK BELEK İCİN
int sektorTip = 0;
int subesayisi = 0, maladet = 0;
double ilkbutce = 1780000.0;
double buyumeoran = 0.02;
double tutar = 0;
double genelbutce = 1780000.0;

double subeMaliyet();
double malucret();
double satisfiyati();

int main()
{
    char yanit1;

    printf("\n===================================================\n");
    printf("        COMPANY SIMULATOR 'e Hosgeldiniz\n");
    printf("===================================================\n");
    printf("sirketinizi kurmaya ve piyasada yukselmeye hazir misiniz? \nCevabinizi belirtin. (E/H)");

    int i = 1;
    while (i != 0)
    {
        scanf(" %c", &yanit1);
        switch (yanit1)
        {
        case 'e':
        case 'E':
            printf("\nsirketinizi kurmaya baslayalim!\n");
            i = 0;
            break;
        case 'H':
        case 'h':
            printf("\nHazir oldugunuzda bildirin!\n");
            break;
        default:
            printf("Lutfen gecerli bir cevap girin\n ");
            break;
        }
    }
    getinfo();
    getcompanytype();

    free(firmaAD);
    return 0;
}

void getcompanytype()
{
    int sektorkod;
    int d = 1;
    while (d != 0)
    {
        printf("Ne sirketi kurmak istersiniz?\nSektor seciniz.\n");
        printf("Ticaret (1) // Turizm (2): ");
        scanf("%d", &sektorkod);

        int c;
        while ((c = getchar()) != '\n' && c != EOF) // ENTER KARAKTERİNİ BUFFERDAN TEMİZLEMEK İCİN
            ;

        switch (sektorkod)
        {
        case 1:
            sektorTip = 1;
            ticaret();
            d = 0;
            break;
        case 2:
            sektorTip = 2;
            turizm();
            d = 0;
            break;
        default:
            printf("Gecersiz secim.\n");
            break;
        }
    }
}
void getinfo()
{
    while (getchar() != '\n' && getchar() != EOF)
        ; // Buffer temizleme (getcompanytype oncesi veya sonrasi kalan karakterler icin)
    char companyname[60];

    printf("//----------------------------------\\\\\n");
    printf("sirket isminizi yaziniz: \n");

    fgets(companyname, sizeof(companyname), stdin);
    // '\n' karakterini temizle
    companyname[strcspn(companyname, "\n")] = '\0';

    firmaAD = (char *)malloc((strlen(companyname) + 1) * sizeof(char));

    if (firmaAD == NULL)
    {
        printf("Hata: Bellek yetersiz!\n");
        exit(1);
    }

    strcpy(firmaAD, companyname);
    printf("%s su anda %.lf dolarlik bir butceye sahip \n\n", firmaAD, genelbutce);

    if (subeMaliyet() > 0)
        printf("\n Butceniz su anda en fazla %d sube olusturmaya yeterli\n\n", (int)(genelbutce / subeMaliyet()));

    printf("//----------------------------------\\\\\n");
    printf("Logonuzu secin\n");
    getlogo();
    printf("\n\n");
}

void ticaret()
{
    char girdi[20];
    float toplamMaliyet = 0;
    int adetgirdi;
    int subeadet = 0;
    int k = 0;
    int sayac0 = 0;

    printf("\n//----------------------------------\\\\\n");
    printf(" sirketiniz resmen piyasada!!!\n");
    printf(" Simulator boyunca yapabilecekleriniz:\n\n");
    printf(" [1] Mevcut Butce Gor\n");
    printf(" [2] Mal Alis/Satis\n");
    printf(" [3] Yeni sube Ac\n");
    printf(" [4] Firma Bilgisi\n");
    printf("\n cikmak icin 'x' e basiniz.\n");
    printf("//----------------------------------\\\\\n");

    while (1)
    {
        scanf("%s", girdi);

        if (strlen(girdi) == 1 && girdi[0] == '1')
        {
            printf("Anlik butce: %.lf\n", genelbutce);
        }
        else if (strlen(girdi) == 1 && girdi[0] == '2')
        {
            printf("\n   --- Mal Alis/Satis ---\n");
            printf("   Satmak veya almak istediginiz mal adetini giriniz.\n");
            printf("   ('-' isareti satis yapmanizi saglar. orn: '-5' 5 adet satar.)\n");
            printf("   Adet: ");

            if (scanf("%d", &adetgirdi) != 1)
            {
                printf("\n HATA: Gecersiz karakter girdiniz! Lutfen sadece tamsayi kullanin.\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                continue;
            }

            double birim_alis = malucret();
            double birim_satis = satisfiyati();

            if (adetgirdi > 0)
            { // MAL ALIsI
                double maliyet = adetgirdi * birim_alis;
                if (genelbutce >= maliyet)
                {
                    genelbutce -= maliyet;
                    maladet += adetgirdi;
                    k += adetgirdi;
                    printf("Isleminiz basarili. Alinan mal adeti: %d. Yeni Butce: %.lf\n", adetgirdi, genelbutce);
                    sayac0++;
                    if (sayac0 >= 10 || adetgirdi > (subesayisi + 1) * 20)
                    {
                        vergi(&genelbutce);
                        printf("\n");
                        sayac0 = 0;
                    }
                }
                else
                {
                    printf("Yetersiz butce! Gereken: %.lf, Mevcut: %.lf\n", maliyet, genelbutce);
                }
            }
            else if (adetgirdi < 0)
            { // MAL SATIsI
                int satilacak_adet = -adetgirdi;
                if (maladet >= satilacak_adet)
                {
                    double gelir = satilacak_adet * birim_satis;
                    genelbutce += gelir;
                    maladet -= satilacak_adet;
                    k += satilacak_adet;
                    printf("Isleminiz basarili. Satilan mal adeti: %d. Yeni Butce: %.lf\n", satilacak_adet, genelbutce);
                    sayac0++;
                    if (sayac0 >= 10)
                    {
                        vergi(&genelbutce);
                        printf("\n");
                        sayac0 = 0;
                    }
                }
                else
                {
                    printf("Stokta yeterli maliniz yok! Mevcut Stok: %d\n", maladet);
                }
            }
            else
            {
                printf("Gecersiz adet girisi (0). Ne alis ne satis yapildi.\n");
            }
        }
        else if (strlen(girdi) == 1 && girdi[0] == '3')
        {
            printf("\n   --- sube Islemleri ---\n");
            printf("   su anda 1 sube ucreti: %.0f $\n", subeMaliyet());
            printf("   Mevcut sube sayisi: %d\n", subesayisi);
            printf("   Kac yeni sube acmak istersiniz?: ");

            if (scanf("%d", &subeadet) != 1)
            {
                printf("Gecersiz giris.\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                continue;
            }

            if (subeadet > 0)
            {
                toplamMaliyet = subeMaliyet() * subeadet;
                if (toplamMaliyet <= genelbutce)
                {
                    subesayisi += subeadet;
                    genelbutce -= toplamMaliyet;
                    printf("%d sube acildi!\n", subeadet);
                    subeadet = 0;
                }
                else
                    printf("Yeterli sermaye kalmadi\n");
            }
            else
                printf("Gecersiz giris\n");
        }
        else if (strlen(girdi) == 1 && girdi[0] == '4')
        {
            printf("\n   ===================================\n");
            printf("     %s FIRMASINA GENEL BAKIs\n", firmaAD);
            printf("   ===================================\n");
            printf("    sube Sayisi       : %d\n", subesayisi);
            printf("    Mevcut Butce      : %f\n", genelbutce);
            printf("    Mal Aktiflik Puani: %d\n", k * 10);
            printf("   ===================================\n");
            subesema(subesayisi);
            printf("\n\n");
            FILE *ptr;
            char *DosyaAd = "FirmaOverwiew.txt";
            if ((ptr = fopen(DosyaAd, "w")) == NULL)
            {
                printf("dosya acarken hata olustu\n");
            }

            fprintf(ptr, "\n   ===================================\n");
            fprintf(ptr, "     %s FIRMASINA GENEL BAKIs\n", firmaAD);
            fprintf(ptr, "   ===================================\n");

            fprintf(ptr, "    sube Sayisi       : %d\n", subesayisi);
            fprintf(ptr, "    Mevcut Butce      : %.2f $\n", genelbutce);
            fprintf(ptr, "    Aktivite Puani (k): %d\n", k * 10);
            fprintf(ptr, "   ===================================\n");
            if (genelbutce == 0)
            {
                fprintf(ptr, " bu firma iflas etmiştir.  \n");
            }
            fclose(ptr);
            printf("\n=================================== FirmaOverwiew dosyasina kayit edildi. ===================================\n");
        }
        else if (strlen(girdi) == 1 && girdi[0] == 'x')
        {
            printf("Programdan cikiliyor...\n");
            free(firmaAD);
            break;
        }
        else
            printf("Yanlis secenek sectiniz.\n");
    }
}

void getlogo()
{
    int logosecenek, favorisayi;
    int i = 0, j = 0, m = 1;
    printf("\n   ==============================================\n");
    printf("     %s FIRMASI IcIN LOGO BELIRLEYIN\n", firmaAD);
    printf("   ==============================================\n");
    while (m)
    {
        printf("Kare(1), ucgen(2), Dikdortgen(3)\n");
        scanf(" %d", &logosecenek);
        if (logosecenek >= 1 && logosecenek <= 3)
        {
            if (logosecenek == 1)
            {
                printf("Favori rakaminizi girin :) ");
                if (scanf("%d", &favorisayi) != 1)
                { /*sonsuz dongu hatasini sayi disinda birsey
girilirse temizle*/
                    printf("HATA: Lutfen sadece sayi giriniz!\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                if (favorisayi >= 0 && favorisayi < 10)
                {
                    for (j = 0; j < 5; j++)
                    {
                        printf("\n");
                        for (i = 0; i < 5; i++)
                        {
                            printf(" %d", favorisayi);
                        }
                    }
                    m = 0;
                }
                else
                    printf("Lutfen gecerli bir sayi girin\n");
            }
            else if (logosecenek == 2)
            {
                printf("Favori rakaminizi girin :) ");
                if (scanf("%d", &favorisayi) != 1)
                { // Buraya da hata kontrolu ekledik
                    printf("HATA: Sayi girmeliydiniz!\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                if (favorisayi >= 0 && favorisayi < 10)
                {
                    for (j = 0; j < 6; j++)
                    {
                        printf("\n");
                        for (i = 0; i < j; i++)
                        {
                            printf(" %d", favorisayi);
                        }
                    }
                    m = 0;
                }
                else
                    printf("Lutfen gecerli bir sayi girin\n");
            }
            else if (logosecenek == 3)
            {
                printf("Favori rakaminizi girin :) ");
                if (scanf("%d", &favorisayi) != 1)
                {
                    printf("HATA: Sayi girmeliydiniz!\n");
                    while (getchar() != '\n')
                        ; // temizle
                    continue;
                }
                if (favorisayi >= 0 && favorisayi < 10)
                {
                    for (j = 0; j < 5; j++)
                    {
                        printf("\n");
                        for (i = 0; i < 8; i++)
                        {
                            printf(" %d", favorisayi);
                        }
                    }
                    m = 0;
                }
                else
                    printf("Lutfen gecerli bir sayi girin\n");
            }
        }
        else
            printf("Yanlis secim yapildi\n");
    }
}

void turizm()
{
    int subeadet = 0;
    char girdi[20];
    float toplamMaliyet = 0;
    int adetgirdi;
    int k = 0;
    int sayac = 0;

    printf("\n//----------------------------------\\\\\n");
    printf(" sirketiniz resmen piyasada!!!\n");
    printf(" Simulator boyunca yapabilecekleriniz:\n\n");
    printf(" [1] Mevcut Butce Gor\n");
    printf(" [2] Gezi Duzenle\n");
    printf(" [3] Yeni sube Ac\n");
    printf(" [4] Firma Bilgisi\n");
    printf("\n cikmak icin 'x' e basiniz.\n");
    printf("//----------------------------------\\\\\n");

    while (1)
    {
        if (scanf("%s", girdi) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            continue;
        }

        if (strlen(girdi) == 1 && girdi[0] == '1')
        {
            printf("Anlik butce: %.lf $\n", genelbutce);
        }
        else if (strlen(girdi) == 1 && girdi[0] == '2')
        {
            printf("\n   --- GEZI DuZENLEME ---\n");
            printf("   %s sirketiniz icin kac gezi planlayacaksiniz?\n", firmaAD);
            printf("   Planlanacak gezi sayisini girin: ");

            if (scanf("%d", &adetgirdi) != 1)
            {
                printf("\n HATA: Gecersiz karakter girdiniz! Lutfen sadece tamsayi kullanin.\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                continue;
            }

            if (adetgirdi > 0)
            {
                float gezi_birim_maliyeti = 500.0;
                float gezi_birim_kazanci = 800.0;

                float toplam_gezi_maliyeti = adetgirdi * gezi_birim_maliyeti;

                if (genelbutce >= toplam_gezi_maliyeti)
                {
                    genelbutce -= toplam_gezi_maliyeti;
                    k += adetgirdi;
                    float gerceklesen_kazanc = adetgirdi * gezi_birim_kazanci;
                    genelbutce += gerceklesen_kazanc;

                    printf("Isleminiz basarili. Duzenlenen Gezi Adeti: %d\n", adetgirdi);
                    printf("Toplam Maliyet: %.2f $. Toplam Kazanc: %.2f $\n", toplam_gezi_maliyeti, gerceklesen_kazanc);
                    printf("Yeni Butce: %.lf $\n", genelbutce);
                    sayac++;
                    if (sayac >= 7 || adetgirdi >= 50)
                    {
                        vergi(&genelbutce);
                        printf("\n");
                        sayac = 0;
                    }
                }
                else
                {
                    printf("Yetersiz butce! Gezi duzenlemek icin gereken: %.2f $. Mevcut: %.lf $\n", toplam_gezi_maliyeti, genelbutce);
                }
            }
            else
            {
                printf("Gecersiz gezi adeti girisi (%d). Gezi planlanmadi.\n", adetgirdi);
            }
        }
        else if (strlen(girdi) == 1 && girdi[0] == '3')
        {
            printf("\n   --- sube Islemleri ---\n");
            printf("   su anda 1 sube ucreti: %.0f $\n", subeMaliyet());
            printf("   Mevcut sube sayisi: %d\n", subesayisi);
            printf("   Kac yeni sube acmak istersiniz?: ");

            if (scanf("%d", &subeadet) != 1)
            {
                printf("\n HATA: Gecersiz karakter girdiniz! Lutfen sadece tamsayi kullanin.\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF)
                    ;
                continue;
            }

            if (subeadet > 0)
            {
                toplamMaliyet = subeMaliyet() * subeadet;
                if (toplamMaliyet <= genelbutce)
                {
                    subesayisi += subeadet;
                    genelbutce -= toplamMaliyet;
                    printf("%d sube acildi!\n", subeadet);
                    subeadet = 0;
                }
                else
                    printf("Yeterli sermaye kalmadi. Gereken: %.2f $\n", toplamMaliyet);
            }
            else
                printf("Gecersiz giris.\n");
        }
        else if (strlen(girdi) == 1 && girdi[0] == '4')
        {
            printf("\n   ===================================\n");
            printf("     %s FIRMASINA GENEL BAKIs\n", firmaAD);
            printf("   ===================================\n");
            printf("    sube Sayisi       : %d\n", subesayisi);
            printf("    Mevcut Butce      : %.2f $\n", genelbutce);
            printf("    Aktivite Puani (k): %d\n", k);
            printf("   ===================================\n");
            subesema(subesayisi);
            printf("\n\n");

            FILE *ptr;
            char *DosyaAd = "FirmaOverwiew.txt";
            if ((ptr = fopen(DosyaAd, "w")) == NULL)
            {
                printf("dosya acarken hata olustu\n");
            }

            fprintf(ptr, "\n   ===================================\n");
            fprintf(ptr, "     %s FIRMASINA GENEL BAKIs\n", firmaAD);
            fprintf(ptr, "   ===================================\n");

            fprintf(ptr, "    sube Sayisi       : %d\n", subesayisi);
            fprintf(ptr, "    Mevcut Butce      : %.2f $\n", genelbutce);
            fprintf(ptr, "    Aktivite Puani (k): %d\n", k);
            fprintf(ptr, "   ===================================\n");
            if (genelbutce == 0)
            {
                fprintf(ptr, " bu firma iflas etmiştir.  \n");
            }
            // firma iflas kontrolü ypatım bilgi verme amaclı
            fclose(ptr);
            printf("\n=================================== FirmaOverwiew dosyasina kayit edildi. ===================================\n");
        }
        else if (strlen(girdi) == 1 && girdi[0] == 'x')
        {
            printf("Programdan cikiliyor...\n");
            break;
        }
        else
            printf("Yanlis secenek girdiniz.\n");
    }
}

double subeMaliyet()
{
    return (ilkbutce / 6) * pow((buyumeoran + 1), subesayisi);
}

double malucret()
{
    return (ilkbutce / 100) * pow((buyumeoran + 1), maladet);
}

double satisfiyati()
{
    return (ilkbutce / 90) * pow((buyumeoran + 1), maladet);
}
void subesema(int miktar)
{
    int satir = 0, sutun = 0, i;
    printf("\n\n");
    for (i = 0; i < miktar / 2; i++)
    {
        printf("            sube %d                 sube %d \n", (i * 2) + 1, (i * 2) + 2);
        for (satir = 0; satir < 4; satir++)
        {
            for (sutun = 0; sutun < 2; sutun++)
            {
                printf("            ***********");
            }
            printf("\n");
        }
        printf("\n");
    }
    if (miktar % 2 != 0)
    {

        int son_sube_no = miktar;

        printf("            sube %d \n", son_sube_no);

        for (satir = 0; satir < 4; satir++)
        {
            printf("            ***********\n");
        }
    }
}

void vergi(double *vergi_ptr)
{
    double vergi_orani = 0.02 + (subesayisi * 0.01);

    double sabit_masraf = 50000 + (subesayisi * 40000.0);

    double toplam_vergi = (*vergi_ptr * vergi_orani) + sabit_masraf;

    if (*vergi_ptr >= toplam_vergi)
    {
        *vergi_ptr -= toplam_vergi;
        printf("\n   [MALIYE]: %d sube icin toplam %.2f $ vergi ve masraf kesildi.\n", subesayisi, toplam_vergi);
        printf("   Kalan Butce: %.2f $\n", *vergi_ptr);
    }
    else
    {
        *vergi_ptr = 0;
        printf("\n   [IFLAS]: %d$ Vergi borcunuzu odeyemediniz! Butce sifirlandi.\n", toplam_vergi);
    }
}