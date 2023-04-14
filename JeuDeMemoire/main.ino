// #include <LiquidCrystal.h>
int displaytime=400;
LiquidCrystal lcd(13,12, 4,18, 2,3 );
int color_array[32];
int input_sequence[32];
int turn=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A3,INPUT);//Bouton3
  pinMode(5,INPUT);//Bouton4
  pinMode(6,INPUT);//Bouton2
  pinMode(7,INPUT);//Bouton1
  pinMode(8,OUTPUT);//Led1
  pinMode(9,OUTPUT);//Led2
  pinMode(10,OUTPUT);//Led3
  pinMode(11,OUTPUT);//Led4
  pinMode(19,OUTPUT);//Buzzer
  randomSeed(analogRead(A0));
  lcd.begin(16, 2);
}
void choix_aleatoire(){
  color_array[turn] = random(8, 12);
}

void jouer_la_sequence(){
  for (int i = 0; i < turn; i++){
    digitalWrite(color_array[i], HIGH);
    delay(displaytime);
    digitalWrite(color_array[i], LOW);
    delay(500);
  }   
}
void get_sequence() {
  int input_sequence[turn];
  for (int i = 0; i < turn; i++) {
    int j;
    while (true) {
      if (digitalRead(7)) {
        j = 8;
        break;
      }
      else if (digitalRead(6)) {
        j = 9;
        break;
      }
      else if (digitalRead(5)) {
        j = 11;
        break;
      }
      else if (digitalRead(A3)) {
        j = 10;
        break;
      }
    }
    digitalWrite(j, HIGH);
    delay(displaytime);
    digitalWrite(j, LOW);
    delay(200);
    input_sequence[i] = j;
  }
}

bool verifier_la_sequence(int color_array[], int input_sequence[], int turn) {
  for (int i = 0; i < turn; i++) {
    if (color_array[i] != input_sequence[i]) {
      return false;
    }
  }
  return true;
}

void affichage_systeme(int turn) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Niveau ");
  lcd.print(turn);
  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(turn - 1);
}
void afficher_menu(){
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print("Appuyez sur ");
  lcd.setCursor(0, 1); 
  lcd.print("un bouton pour");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("un bouton pour");
  lcd.setCursor(0,1);
  lcd.print("change de niveau");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("change de niveau");
  lcd.setCursor(0,1);
  lcd.print("de difficulte");
  delay(500);
    if (digitalRead(7)==1){//Easy
      displaytime=3000;
    }
    else if(digitalRead(6)==1){//Medium
      displaytime=500;
    }
    else if(digitalRead(5)==1){//Impossible
      displaytime=25;
    }
    else if(digitalRead(A3)==1){//Hard
      displaytime=300;      
    }
    if (displaytime!=400){
      jeu();
      displaytime=400;
    }
}
void jeu(){
    turn=0;
    while(true){//Boucle de jeu
      affichage_systeme(turn);
      choix_aleatoire();
      jouer_la_sequence();
      get_sequence();
      if (verifier_la_sequence(color_array, input_sequence, turn)==1){
        digitalWrite(19,HIGH);
        delay(500);
        digitalWrite(19,LOW); 
        break;
      }
        
        turn++;
        }
}
void loop() {

  afficher_menu();
}