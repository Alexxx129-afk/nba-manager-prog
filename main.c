#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define spavaj(x) Sleep(x*1000)

typedef struct {
    char ime[50];
    char ekipa[50];
    long int cena;
    int ovr;
} Igrac;

int izborKonf()
{
    int broj;
    do {
        printf("\n==========================\n");
        printf("1. Istocna konferencija\n");
        printf("2. Zapadna konferencija\n");
        printf("Izaberi konferenciju (1 ili 2): ");
        scanf("%d", &broj);

        if (broj < 1 || broj > 2) {
            printf("Greska! Unesite 1 za Istok ili 2 za Zapad.\n");
        }
    } while(broj < 1 || broj > 2);
    printf("==========================\n");
    return broj;
}

int izbor()
{
    int broj;
    do
    {
        printf("Unesi broj za izbor ekipe (1-15): ");
        scanf("%d", &broj);

        if (broj < 1 || broj > 15)
            printf("Greska! Molimo unesite broj izmedju 1 i 15.\n\n");
    } while(broj > 15 || broj < 1);

    return broj;
}

int ucitajIgrace(Igrac svi_igraci[], int max_kapacitet) {
    FILE *fajl = fopen("igraci.txt", "r");
    if (fajl == NULL) {
        printf("Greska: Ne mogu da otvorim fajl 'igraci.txt'!\n");
        return -1;
    }

    int brojac = 0;
    while (brojac < max_kapacitet && fscanf(fajl, " %[^,],%[^,],%ld,%d\n",
                  svi_igraci[brojac].ime,
                  svi_igraci[brojac].ekipa,
                  &svi_igraci[brojac].cena,
                  &svi_igraci[brojac].ovr) == 4) {
        brojac++;
    }
    fclose(fajl);
    return brojac;
}

int izvuciTimove(Igrac svi_igraci[], int broj_igraca, char timovi[30][50]) {
    int broj_timova = 0;
    for (int i = 0; i < broj_igraca; i++) {
        int vec_postoji = 0;
        for (int j = 0; j < broj_timova; j++) {
            if (strcmp(svi_igraci[i].ekipa, timovi[j]) == 0) {
                vec_postoji = 1;
                break;
            }
        }
        if (vec_postoji == 0) {
            strcpy(timovi[broj_timova], svi_igraci[i].ekipa);
            broj_timova++;
            if (broj_timova == 30) break;
        }
    }
    return broj_timova;
}

void ispisiRoster(Igrac svi_igraci[], int broj_igraca, char trazeni_tim[]) {
    system("cls");
    int pronadjeno = 0;
    printf("\n==================================================\n");
    printf("           ROSTER TIMA: %s\n", trazeni_tim);
    printf("==================================================\n");
    printf("%-20s | %-5s | %-12s\n", "IME IGRACA", "OVR", "CENA/PLATA");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < broj_igraca; i++) {
        if (strcmp(svi_igraci[i].ekipa, trazeni_tim) == 0) {
            printf("%-20s | %-5d | $%ld\n",
                   svi_igraci[i].ime,
                   svi_igraci[i].ovr,
                   svi_igraci[i].cena);
            pronadjeno++;
        }
    }
    printf("==================================================\n");
    printf("Ukupno pronadjeno igraca: %d\n", pronadjeno);
}
void ispisi_opcije()
{
    printf("==================================================\n");
    printf("1.Odigraj utakmicu\n");
    printf("2.Pregled ekipe\n");
    printf("3.Prikaz tabele\n");
    printf("4.Izlaz\n");
    printf("==================================================\n");
}
int izbor_meni()
{
    int broj;
    printf("Unesi broj za izbor opcije:");
    do
    {
        scanf("%d",&broj);
        if (broj < 1 || broj > 4)
            printf("Greska! Molimo unesite broj izmedju 1 i 4.\n\n");
    }while(broj < 1 || broj > 4);
    return broj;
}
void meni(Igrac svi_igraci[], int broj_igraca, char trazeni_tim[])
{
    system("cls");
    ispisi_opcije();
    int broj = izbor_meni();
    switch(broj)
    {
    case 1:
        //kod za utakmicu...
        break;
    case 2:
        ispisiRoster(svi_igraci, broj_igraca, trazeni_tim);
        break;
    case 3:
        //kod za prikazivanje tabele...
        break;
    case 4:
        printf("Gasim igricu Hvala na igranju!");
        spavaj(2);
        exit(0);
    }
}
int main()
{
    Igrac svi_igraci[1000];
    char timovi[30][50];

    int broj_igraca = ucitajIgrace(svi_igraci, 1000);
    if (broj_igraca == -1) return 1;

    izvuciTimove(svi_igraci, broj_igraca, timovi);

    int konf = izborKonf();
    int start_index = (konf == 1) ? 15 : 0;

    printf("\n=== IZABERITE SVOJ TIM ===\n");
    for (int i = 0; i < 15; i++) {
        printf("%d. %s\n", i + 1, timovi[start_index + i]);
    }
    printf("==========================\n");

    int izabran_broj = izbor();
    int stvarni_indeks = start_index + (izabran_broj - 1);

    ispisiRoster(svi_igraci, broj_igraca, timovi[stvarni_indeks]);
    spavaj(5);
    meni(svi_igraci, broj_igraca, timovi[stvarni_indeks]);

    return 0;
}
