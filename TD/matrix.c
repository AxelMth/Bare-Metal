#include "registerManager.h"
#include "matrix.h"
#include "globalObjects.h"

extern char _binary_image_raw_start;

// Définition des registres de configuration des broches en GPIO
// Port A
#define PORTA_PCR4 (*(volatile uint32_t *)0x40049010)
#define PORTA_PCR12 (*(volatile uint32_t *)0x40049030)
#define PORTA_PCR13 (*(volatile uint32_t *)0x40049034)

// Port B
#define PORTB_PCR0 (*(volatile uint32_t *)0x4004A000)
#define PORTB_PCR1 (*(volatile uint32_t *)0x4004A004)
#define PORTB_PCR2 (*(volatile uint32_t *)0x4004A008)

// Port C
#define PORTC_PCR8 (*(volatile uint32_t *)0x4004B020)
#define PORTC_PCR9 (*(volatile uint32_t *)0x4004B024)

// Port D
#define PORTD_PCR2 (*(volatile uint32_t *)0x4004C008)
#define PORTD_PCR4 (*(volatile uint32_t *)0x4004C010)
#define PORTD_PCR5 (*(volatile uint32_t *)0x4004C014)
#define PORTD_PCR6 (*(volatile uint32_t *)0x4004C018)
#define PORTD_PCR7 (*(volatile uint32_t *)0x4004C01C)

// Définition des registres de configuration des broches en sortie
#define GPIOA_PDDR (*(volatile uint32_t *)0x400FF014)
#define GPIOB_PDDR (*(volatile uint32_t *)0x400FF054)
#define GPIOC_PDDR (*(volatile uint32_t *)0x400FF094)
#define GPIOD_PDDR (*(volatile uint32_t *)0x400FF0D4)

// Définition des registres de configuration des broches en sortie
#define GPIOA_PSOR (*(volatile uint32_t *)0x400FF004)
#define GPIOB_PSOR (*(volatile uint32_t *)0x400FF044)
#define GPIOC_PSOR (*(volatile uint32_t *)0x400FF084)
#define GPIOD_PSOR (*(volatile uint32_t *)0x400FF0C4)

// Définition des registres de configuration des broches en sortie
#define GPIOA_PCOR (*(volatile uint32_t *)0x400FF008)
#define GPIOB_PCOR (*(volatile uint32_t *)0x400FF048)
#define GPIOC_PCOR (*(volatile uint32_t *)0x400FF088)
#define GPIOD_PCOR (*(volatile uint32_t *)0x400FF0C8)

// Définition des fonctions d'initialisation des broches du driver
static inline void RST(int x) {if(!x) {SETONEBIT(GPIOB_PCOR,2);} else {SETONEBIT(GPIOB_PSOR,2);}};
static inline void SB(int x) {if(!x) {SETONEBIT(GPIOB_PCOR,0);} else {SETONEBIT(GPIOB_PSOR,0);}};
static inline void LAT(int x) {if(!x) {SETONEBIT(GPIOB_PCOR,1);} else {SETONEBIT(GPIOB_PSOR,1);}};
static inline void SCK(int x) {if(!x) {SETONEBIT(GPIOC_PCOR,8);} else {SETONEBIT(GPIOC_PSOR,8);}};
static inline void SDA(int x) {if(!x) {SETONEBIT(GPIOC_PCOR,9);} else {SETONEBIT(GPIOC_PSOR,9);}};
static inline void ROW0(int x) {if(!x) {SETONEBIT(GPIOA_PCOR,13);} else {SETONEBIT(GPIOA_PSOR,13);}};
static inline void ROW1(int x) {if(!x) {SETONEBIT(GPIOD_PCOR,2);} else {SETONEBIT(GPIOD_PSOR,2);}};
static inline  void ROW2(int x) {if(!x) {SETONEBIT(GPIOD_PCOR,4);} else {SETONEBIT(GPIOD_PSOR,4);}};
static inline void ROW3(int x) {if(!x) {SETONEBIT(GPIOD_PCOR,6);} else {SETONEBIT(GPIOD_PSOR,6);}};
static inline void ROW4(int x) {if(!x) {SETONEBIT(GPIOD_PCOR,7);} else {SETONEBIT(GPIOD_PSOR,7);}};
static inline void ROW5(int x) {if(!x) {SETONEBIT(GPIOD_PCOR,5);} else {SETONEBIT(GPIOD_PSOR,5);}};
static inline void ROW6(int x) {if(!x) {SETONEBIT(GPIOA_PCOR,12);} else {SETONEBIT(GPIOA_PSOR,12);}};
static inline void ROW7(int x) {if(!x) {SETONEBIT(GPIOA_PCOR,4);} else {SETONEBIT(GPIOA_PSOR,4);}};

// Désactive toutes les lignes
static void desactivate_row();

// Active la ligne row
static void activate_row(int row);

// Génère un pulse du signal SCK
static void pulse_SCK();

// Génère un pusle du signal LAT
static void pulse_LAT();

// Mets tous les bits du registres à décalage à 1
static void init_bank0();

// Envoie au bank spécifié l'entier sur 8 bits
static void send_byte(uint8_t val, int bank);

// Met à jour tous les bits de la ligne
static void mat_set_row(int row, const rgb_color *val);

static inline void wait(int delay){
  for (int i = 0; i < delay*5000; i++)
    asm volatile ("nop");
}

// Processus d'initialisation de la matrice de LEDs
void matrix_init(){


  // Mise en marche des horloges
  SIM_SCGC5 |= 0x00001E00;

  // Mode GPIO
  PORTB_PCR0  = 0x00000103;
  PORTB_PCR1  = 0x00000103;
  PORTB_PCR2  = 0x00000103;
  PORTC_PCR8  = 0x00000103;
  PORTC_PCR9  = 0x00000103;
  PORTA_PCR13 = 0x00000103;
  PORTD_PCR2  = 0x00000103;
  PORTD_PCR4  = 0x00000103;
  PORTD_PCR6  = 0x00000103;
  PORTD_PCR7  = 0x00000103;
  PORTD_PCR5  = 0x00000103;
  PORTA_PCR12 = 0x00000103;
  PORTA_PCR4  = 0x00000103;

  // Mode sortie
  GPIOA_PDDR |= (1<<4) | (1<<12) | (1<<13);
  GPIOB_PDDR |= (1<<0) | (1<<1) | (1<<2);
  GPIOC_PDDR |= (1<<8) | (1<<9);
  GPIOD_PDDR |= (1<<2) | (1<<4) | (1<<5) | (1<<6) | (1<<7);

  // Initialisation des signaux
  RST(0);
  SB(1);
  LAT(1);
  SCK(0);
  SDA(0);
  desactivate_row();

  // Attente de 100ms
  wait(100);

  RST(1);

  init_bank0();

}

static void pulse_SCK(){

  SCK(0);
  SCK(1);
  SCK(0);
}

static void pulse_LAT(){

  LAT(1);
  LAT(0);
  LAT(1);
}

static void activate_row(int row){
  switch(row){
    case 0:
      ROW0(1);
      break;
    case 1:
      ROW1(1);
      break;
    case 2:
      ROW2(1);
      break;
    case 3:
      ROW3(1);
      break;
    case 4:
      ROW4(1);
      break;
    case 5:
      ROW5(1);
      break;
    case 6:
      ROW6(1);
      break;
    case 7:
      ROW7(1);
      break;
  }
}

static void desactivate_row(){

  ROW0(0);
  ROW1(0);
  ROW2(0);
  ROW3(0);
  ROW4(0);
  ROW5(0);
  ROW6(0);
  ROW7(0);

}

static void send_byte(uint8_t val, int bank){

  // Longueur du registre à décalage donné en argument
  int length = 8;
  SB(bank);

  if (!bank)
    length = 6;

  // Rentre dans SDA chaque bit de val (val[7] ... val[0])
  for (int i = 0; i < length; i++){
    SDA(val & (1<<(length-(i+1))));
    pulse_SCK();
  }

}

static void mat_set_row(int row, const rgb_color *val) {

  // Pour chaque pixels de la ligne, on met dans Bank1 la valeur de chaque
  // pixel.
  for (int i=7; i>=0; i--){
    send_byte(val[i].b,1);
    send_byte(val[i].g,1);
    send_byte(val[i].r,1);
  }
  pulse_LAT();
  // Une fois les données envoyées, on active la ligne
  activate_row(row);
}

static void init_bank0(){
  for (int i = 0; i < 24; i++)
    send_byte(0b11111111,0);
  pulse_LAT();
}

void test_pixels(){

  rgb_color val[8];

  while(1){

    int k;
    for (k = 0; k <= 7; k++)
      	desactivate_row();

    // Dégradé de rouge
    for (int i = 0; i < 8; i++) {
      	val[i].r = 255 >> i;
      	val[i].g = 0;
    	  val[i].b = 0;
    }

    // Activation des lignes successivement
    for (int j = 0; j < 8; j++){
      mat_set_row(j, val);
      wait(100);
      desactivate_row();
    }

    // Dégradé de vert
    for (int i = 0; i < 8; i++) {
      val[i].r = 0;
      val[i].g = 255 >> i;
      val[i].b = 0;
    }

    // Activation des lignes successivement
    for (int j = 0; j < 8; j++){
      mat_set_row(j, val);
      wait(100);
      desactivate_row();
    }

    // Dégradé de bleu
    for (int i = 0; i < 8; i++) {
      val[i].r = 0;
      val[i].g = 0;
      val[i].b = 255 >> i;
    }

    // Activation des lignes successivement
    for (int j = 0; j < 8; j++){
      mat_set_row(j, val);
      wait(100);
      desactivate_row();
    }
  }
}

void display_image(){

  // Adresse du premier octet de la ligne 1
  const char * current = &_binary_image_raw_start;

  // On intère sur les 8 lignes
  for (int i = 0 ; i < 8; i++){

    // On laisse la ligne précédente allumée pour avoir une meilleure intensité
    // sans que l'oeil ne percoive le rafraichissement des lignes
    wait(3);

    // On rafraichit les lignes définies par le mat_set_row de l'itération précédente
    desactivate_row();

    // Tableau qui contiendra les couleurs pour une ligne de LEDs
    rgb_color val[8];

    // Pour chaque ligne on remplit val par les valeurs RDG de chaque LED
    for (int j = 7; j >= 0; j--){
      val[j].r = *current++;
      val[j].g = *current++;
      val[j].b = *current++;
    }
    // On affiche la ligne de LEDs (dans le même ordre que la photo du TP)
    mat_set_row(8-(i+1),val);
  }
}

void display_frame(){
	// On rafraîchit l'image en permanence
   	// Pour chaque ligne
	for (int i = 0; i < 8; i++){
		// On attend que display soit à 1 (ie on attend PIT_LDVAL0 cycles puis on le remet à0
		while(!display);
		display = 0;
      		// On désactive les lignes pour n'afficher que la ligne courante
		desactivate_row();
      		// Affichage de la ligne avec les valeurs de frame
		mat_set_row(i,frame+8*i);
	}
}
