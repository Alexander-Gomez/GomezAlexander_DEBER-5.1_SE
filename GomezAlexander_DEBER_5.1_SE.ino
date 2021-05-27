#include <Keypad.h>
#include <LiquidCrystal.h>   
#include <EEPROM.h>
//Inicializamos el teclado matricial
const byte filas = 4; 
const byte columnas = 4;
int i=0;
int j=0;
int aux=0;
int pos=0;
char key;
byte pinfilas[]  = {7,6,5,4};
byte pincolumnas[] = {3,2,1,0};
char teclas[filas][columnas] = {
  {'7','8','9','A'},
  {'4','5','6','B'},
  {'1','2','3','C'},
  {'*','0','#','D'}
                                };
Keypad teclado = Keypad( makeKeymap(teclas), pinfilas, pincolumnas, filas, columnas); 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);              //indicamos los pines al cual esta conectado el lcd.
void setup() {
lcd.begin(16, 2);   
teclado.setHoldTime(1000); 
lcd.setCursor(1,0);
lcd.println(String("Gomez Alexander"));               //mensaje inicial.
lcd.setCursor(4,1);
lcd.println("DEBER 5.1");
delay(500);
lcd.clear();
}
void loop() {
  key=teclado.getKey();
  if(key<='9' && key>='0'){                           //indicamos los valores validos para iniciar con el teclado
    lcd.home();
    lcd.println(String("Valor: "));                   //pedimos que ingresen los valores
   if(i<4){                                           //ciclo para pedir 4 numeros recordar que en programacion las posiciones empiezan desde el 0
    lcd.setCursor(0,1);
    lcd.print(key);
    EEPROM.put(pos,key);                              //guardamos el valor del teclado en la posicion 0
    pos++;                                            //aumentamos la variable de la posicion para ir guardando los valores en cada una de las posiciones
    lcd.setCursor(7,0);
    lcd.println(i);
    delay(500);
    lcd.clear();
    i++;                                              //aumentamos nuestro contador para el ciclo if               
  }else{
    lcd.setCursor(0,0);
    lcd.println(String("Solo 4 digitos"));            //Mensaje que indica que no vale ingresar mas de 4 digitos.
    delay(500);
    lcd.clear();
    }
  }
  else if(key=='B'){
      char key1 = EEPROM.get(0,key);                  //Obtenemos los datos guardados en la EEPROM.
      char key2 = EEPROM.get(1,key);
      char key3 = EEPROM.get(2,key);
      char key4 = EEPROM.get(3,key);
      
      char vect[4] = {key1,key2,key3,key4};           //Almacenamos los valores en un vector
      
     for(i=0;i<4;i++){                                //inicia el metodo de ordenamiento
      for(j=i+1;j<4;j++){                             //El metodo usado es el metodo por intercambio  
        if(vect[i]>vect[j]){
          aux=vect[i];
          vect[i]=vect[j];
          vect[j]=aux;
          }
        }
      }
      
      lcd.clear();
      lcd.home();
      lcd.print(String("1) ")+vect[0]);               //Impresion desde la posicion menor a mayor
      lcd.setCursor(0,1);
      lcd.print(String("2) ")+vect[1]);
      lcd.setCursor(7,0);
      lcd.print(String("3) ")+vect[2]);
      lcd.setCursor(7,1);
      lcd.print(String("4) ")+vect[3]);
      delay(2000);
      lcd.clear(); 
      lcd.setCursor(4,0);
      lcd.println(String("FIN"));
      delay(500);
      lcd.clear();
      }
} 
  
