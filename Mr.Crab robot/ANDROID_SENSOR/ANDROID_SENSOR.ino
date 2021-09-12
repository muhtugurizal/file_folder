//==========================================================================================
//
//  Program dikendalikan menguanakan modul bluetooth Hc-05
//  Robot ini di desain oleh Microbot indonesia
//  mengunakan servo 8 MG90S,sensor hc-sr04, arduino uno, shild sensor dan chassis
//  Chassis bisa anda dapatkan di (https://www.tokopedia.com/microbot/robot-spider-quadruped-servo-sg90s-only-chassis?trkid=f=Ca0000L000P0W0S0Sh00Co0Po0Fr0Cb0_src=shop-product_page=1_ob=11_q=_catid=36_po=6)
//  Progam ini di buat ulang (remixing) oleh Misbah najh (FB)
//
//==========================================================================================

#include <Servo.h>    // servo library
#include <SoftwareSerial.h>
//////inisialisai bluetooth///
String data;
SoftwareSerial mySerial(13 , 12); //rx.tx
//////inisialisasi sensor ping///
#include <NewPing.h>
///sensor depan
#define triger1  9  // 
#define echo1    8  // 
#define jarak_max1 99
NewPing sonar1(triger1, echo1, jarak_max1);
///sensor kanan
#define triger2  6  // 
#define echo2    7  // 
#define jarak_max2 99
NewPing sonar2(triger2, echo2, jarak_max2);
///sensor kiri
#define triger3  5 // 
#define echo3    4  // 
#define jarak_max3 99
NewPing sonar3(triger3, echo3, jarak_max3);
// kalibrasi
int da =  -12,  // kaki kiri depan
    db =   10,  // kaki kiri belakang
    dc =  -18,  // kaki kanan belakang
    dd =   12;  // kaki kanan depan

// servo initial positions + calibration
int a90  = (90  + da),
    a120 = (120 + da),
    a150 = (150 + da),
    a180 = (180 + da);

int b0   = (0   + db),
    b30  = (30  + db),
    b60  = (60  + db),
    b90  = (90  + db);

int c90  = (90  + dc),
    c120 = (120 + dc),
    c150 = (150 + dc),
    c180 = (180 + dc);

int d0   = (0   + dd),
    d30  = (30  + dd),
    d60  = (60  + dd),
    d90  = (90  + dd);

// point untuk memulai servo
int s11 = 90; // kaki kiri depan servo(1) 
int s12 = 90; // kaki kiri atas  depan servo(2)
int s21 = 90; // kaki kiri belakang servo(3)
int s22 = 90; // kaki kiri belakang atas servo(4)
int s31 = 90; // kaki kanan belakang servo(5)
int s32 = 90; // kaki kanan belakang atas servo(6)
int s41 = 90; // kaki kanan depan servo(7)
int s42 = 90; // kaki kanan atas depan servo(8)

int f    = 0;
int b    = 0;
int l    = 0;
int r    = 0;
int spd  = 3;   // inisialisai kecepatan gerak
int high = 0;   // inisialisai ketingian robot berdiri

// Define 8 Servo
Servo myServo1; // kaki kiri depan servo(1) 
Servo myServo2; // kaki kiri bawah  depan servo(2)
Servo myServo3; // kaki kiri belakang servo(3)
Servo myServo4; // kaki kiri belakang bawah servo(4)
Servo myServo5; // kaki kanan belakang servo(5)
Servo myServo6; // kaki kanan belakang bawah servo(6)
Servo myServo7; // kaki kanan depan servo(7)
Servo myServo8; // kaki kanan bawah depan servo(8)

//===== Setup ==============================================================================

void setup()
{
 mySerial.begin(9600);
 
  // peletakan servo pada pin Arduino 
  myServo1.attach(2);  // kaki kiri depan servo(1)
  myServo2.attach(3);  // kaki kiri bawah depan servo(2)
  myServo3.attach(10);  // kaki kiri belakang servo(3)
  myServo4.attach(11);  // kaki kiri belakang bawah servo(4)
  myServo5.attach(A0); // kaki kanan belakang servo(5)
  myServo6.attach(A1); // kaki kanan belakang bawah servo(6)
  myServo7.attach(A4); // kaki kanan depan servo(7)
  myServo8.attach(A5); // kaki kanan bawah depan servo(8)
 
}
void set1(){
  myServo1.attach(A4); myServo2.attach(A5);
  myServo3.attach(2);  myServo4.attach(3);  
  myServo5.attach(10); myServo6.attach(11); 
  myServo7.attach(A0); myServo8.attach(A1); 
}
void set2(){
  myServo1.attach(2);  myServo2.attach(3);
  myServo3.attach(10); myServo4.attach(11);  
  myServo5.attach(A0); myServo6.attach(A1); 
  myServo7.attach(A4); myServo8.attach(A5); 
}

//== Loop ==================================================================================

void loop()
{ int jarak1 = sonar1.ping_cm();
  int jarak2 = sonar2.ping_cm();
  int jarak3 = sonar3.ping_cm( );
  Serial.print(jarak1);
  Serial.print("  ");
  Serial.print(jarak2);
  Serial.print("  ");
  Serial.println(jarak3);
  Serial.print("  ");
  
  high = 15;        // Set ketingian berdiri hingga 15
  spd = 7     ;          // Set kecepatan max 3

if ( mySerial.available()>0){ 
      delay(100);
      char c=mySerial.read();
      data +=c;
   }  
      if (data.length()>0){
      Serial.print(data);

      if (data=="0"){
      maju();
      delay(50);
      }
      else if(data=="1"){
      mundur();
      delay(50);
      }
      else if(data=="2"){
      belok_kanan();
     delay(50);
      }
      else if(data=="3"){
      belok_kiri();
     delay(50);
      }
      else if(data=="4"){
      nantang();
     delay(5000);
      }
      else if(data=="5"){
      anjing();
     delay(50);
      }
      else if(data=="6"){
      naik_kanan();
     delay(1000);
      naik_kiri();
     delay(1000);
      }
       else if(data=="7"){
      duduk();
      delay(2000);
      berdiri();
      delay(6000);
      
      }
      else if(data=="8"){
      kuda();
      delay(3000);
      }
      else if(data=="9"){
      perpisahan();
      delay(1000);
      }
     data="";
     servo_tengah();
    }
    
     
     else if (jarak1<15 && jarak1>1){
              //jika sensor kiri < sensor kanan maka ditentukan "balik kanan"
              if (jarak1<jarak3){
              mundur();
              balik_kiri();
              }
              //jika sensor kanan > sensor kanan maka ditentukan "balik kiri"
              else if (jarak1>jarak3){
              mundur();
              balik_kanan();
               }
          }
          else if (jarak2<15 && jarak2>1){
            geser_kiri();
          }
          else if (jarak3<15 && jarak3>1){
            geser_kanan();
          }
         
          else{
            servo_tengah();
          }
          
   servo_tengah();
   }
  
         
      

//== perpisahan ==================================================================================

void perpisahan()
{
  servo_tengah();
  myServo4.write(45);
  myServo6.write(45);
  delay(200);
  myServo8.write(0);
  delay(200);
  myServo7.write(180);
  delay(200);
  myServo7.write(30);
  delay(300);
  myServo7.write(180);
  delay(300);
  myServo7.write(30);
  delay(300);
  myServo7.write(s41);
  delay(300);
  myServo8.write(s42);
  servo_tengah();

}

//== merunduk ===================================================================================

void merunduk()
{
  myServo2.write(15);
  myServo8.write(15);
  delay(700);
  myServo2.write(90);
  myServo8.write(90);
  delay(700);
}

void berdiri(){
  int x=150;
  myServo2.write(x);
  myServo4.write(x);
  myServo6.write(x);
  myServo8.write(x);
}
void duduk(){
  int x=20;
  myServo1.write(x);
  myServo3.write(x);
  myServo5.write(x);
  myServo7 .write(x);
  int y=15;
  myServo2.write(y);
  myServo4.write(y);
  myServo6.write(y);
  myServo8.write(y);
}
void nantang(){
  myServo2.write(150);
  myServo4.write(15);
  myServo6.write(15);
  myServo8.write(150);
}
void kuda(){
  myServo1.write(30);
  myServo3.write(150);
  myServo5.write(30);
  myServo7.write(150);
  delay(1000);
  myServo2.write(150);
  myServo8.write(150);
  delay(3000);
}
void anjing(){
  myServo2.write(30);
  myServo3.write(30);
  myServo4.write(30);
  myServo5.write(170);
  myServo6.write(30);
  myServo8.write(30);
  delay(2000);
  myServo1.write(30);
  myServo7.write(150);
  delay(2000);
  myServo2.write(150);
  myServo8.write(150);
  delay(1000);
  myServo2.write(30);
  myServo8.write(150);
  delay(200);
  myServo2.write(150);
  myServo8.write(30);
  delay(200);
  myServo2.write(15);
  myServo8.write(150);
  delay(200);
  myServo2.write(150);
  myServo8.write(15);
  delay(200);
  myServo2.write(30);
  myServo8.write(150);
  delay(200);
  myServo2.write(150);
  myServo8.write(30);
  delay(200);
  myServo2.write(30);
  myServo8.write(150);
  delay(200);
  myServo2.write(30);
  myServo8.write(30 );
  delay(2000);

  /////diam////
  myServo2.write(150);
  myServo8.write(30);
  delay(200);
  myServo2.write(30);
  myServo8.write(150);
  delay(200);
  myServo2.write(150);
  myServo8.write(30);
  delay(200);
  myServo2.write(30);
  myServo8.write(150);
  delay(200);
  myServo2.write(150);
  myServo8.write(30);
  delay(200);
  myServo2.write(30);
  myServo8.write(150);
  delay(200);
  myServo2.write(150);
  myServo8.write(150);
  delay(2000);
  
  
}

void merdeka(){
  //pivot
  myServo1.write(90);
  myServo3.write(15);
  myServo5.write(90);
  myServo7.write(150);
  //lift
  myServo2.write(15);
  myServo4.write(150);
  myServo6.write(15);
  myServo8.write(150);
  delay(1000);
  myServo1.write(180);
  delay(200);
  myServo1.write(30);
  delay(200);
  myServo1.write(180);
  delay(200);
  myServo1.write(30);
  delay(200);
  myServo1.write(30);
  delay(200);
 }
 
//== naik_kiri =============================================================================

void naik_kiri()
{
  myServo2.write(15);
  myServo4.write(15);
  myServo6.write(150);
  myServo8.write(150);
}

//== naik_kanan ============================================================================

void naik_kanan()
{
  myServo2.write(150);
  myServo4.write(150);
  myServo6.write(15);
  myServo8.write(15);
}

//== maju ===============================================================================

void maju()
{
  // menghitung poin

  // kaki kiri depan
  a90 = (90 + da),
  a120 = (120 + da),
  a150 = (150 + da),
  a180 = (180 + da);

  // kaki kiri belakang
  b0 = (0 + db),
  b30 = (30 + db),
  b60 = (60 + db),
  b90 = (90 + db);

  // kaki kanan belakang
  c90 = (90 + dc),
  c120 = (120 + dc),
  c150 = (150 + dc),
  c180 = (180 + dc);

  // kaki kanan depan
  d0 = (0 + dd),
  d30 = (30 + dd),
  d60 = (60 + dd),
  d90 = (90 + dd);
  
  // set posisi servo dan kecepatan yang dibutuhkan untuk sekali berjalan maju 
  // KkiD (kaki kiri depan) KkaB (kaki kanan Belakang)
  // (KkiD,KkiB, KkaB,  KkaD, KkiAD, KkiAB, KkaAB, KkaAD, S1, S2, S3, S4)
  srv(a180, b0 , c120, d60, 42,  33,  33,  42,  1,  3,  1,  1);
  srv( a90, b30, c90,  d30, 6,   33,  33,  42,  3,  1,  1,  1);
  srv( a90, b30, c90,  d30, 42,  33,  33,  42,  3,  1,  1,  1);
  srv(a120, b60, c180, d0,  42,  33,  6,   42,  1,  1,  3,  1);
  srv(a120, b60, c180, d0,  42,  33,  33,  42,  1,  1,  3,  1);
  srv(a150, b90, c150, d90, 42,  33,  33,  6,   1,  1,  1,  3);
  srv(a150, b90, c150, d90, 42,  33,  33,  42,  1,  1,  1,  3);
  srv(a180, b0,  c120, d60, 42,  6,   33,  42,  1,  3,  1,  1);
   
}

//== mundur ==================================================================================

void mundur()
{
  // set posisi servo dan kecepatan yang dibutuhkan untuk sekali berjalan mundur
  // (KkiD.1,KkiB.3,KkaB.5,KkaD.7,KkiAD.2,KkiAB.4,KkaAB.6, KkaAD.8, S1, S2, S3, S4)
  srv(180, 0,  120, 60, 42, 33, 33, 42, 3,  1, 1, 1);//3=5//S2=s3
  srv(150, 90, 150, 90, 42, 18, 33, 42, 1,  3, 1, 1);//1=7//s1=s4
  srv(150, 90, 150, 90, 42, 33, 33, 42, 1,  3, 1, 1);
  srv(120, 60, 180, 0,  42, 33, 33, 6,  1,  1, 1, 3);
  srv(120, 60, 180, 0,  42, 33, 33, 42, 1,  1, 1, 3);
  srv(90,  30, 90,  30, 42, 33, 18, 42, 1,  1, 3, 1);
  srv(90,  30, 90,  30, 42, 33, 33, 42, 1,  1, 3, 1);
  srv(180, 0,  120, 60, 6,  33, 33, 42, 3,  1, 1, 1);
  

}

//== belok_kiri =================================================================================

void belok_kiri()
{
  // set posisi servo dan kecepatan yang dibutuhkan untuk sekali belok kiri
  // (KkiD,KkiB,KkaB,KkaD,KkiAD,KkiAB,KkaAB,KkaAD,S1,S2,S3,S4)
  srv(150,  90, 90,  30, 42, 6,  33, 42, 1, 3, 1, 1);
  srv(150,  90, 90,  30, 42, 33, 33, 42, 1, 3, 1, 1);
  srv(120,  60, 180, 0,  42, 33, 6,  42, 1, 1, 3, 1);
  srv(120,  60, 180, 0,  42, 33, 33, 24, 1, 1, 3, 1);
  srv(90,   30, 150, 90, 42, 33, 33, 6,  1, 1, 1, 3);
  srv(90,   30, 150, 90, 42, 33, 33, 42, 1, 1, 1, 3);
  srv(180,  0,  120, 60, 6,  33, 33, 42, 3, 1, 1, 1);
  srv(180,  0,  120, 60, 42, 33, 33, 33, 3, 1, 1, 1);
}

//== belok_kanan ================================================================================

void belok_kanan ()
{
  // set posisi servo dan kecepatan yang dibutuhkan untuk sekali belok kanan
  // (KkiD,KkiB,KkaB,KkaD,KkiAD,KkiAB,KkaAB,KkaAD,S1,S2,S3,S4)
  srv( 90, 30, 150, 90, 6,  33, 33, 42, 3, 1, 1, 1);
  srv( 90, 30, 150, 90, 42, 33, 33, 42, 3, 1, 1, 1);
  srv(120, 60, 180, 0,  42, 33, 33, 6,  1, 1, 1, 3);
  srv(120, 60, 180, 0,  42, 33, 33, 42, 1, 1, 1, 3);
  srv(150, 90, 90,  30, 42, 33, 6,  42, 1, 1, 3, 1);
  srv(150, 90, 90,  30, 42, 33, 33, 42, 1, 1, 3, 1);
  srv(180, 0,  120, 60, 42, 6,  33, 42, 1, 3, 1, 1);
  srv(180, 0,  120, 60, 42, 33, 33, 42, 1, 3, 1, 1);
}
void balik_kanan(){
  belok_kanan();
  belok_kanan();
}
void balik_kiri(){
  belok_kiri();
  belok_kiri();
}
void geser_kanan(){
  set1();maju();set2();
}
void geser_kiri(){
  set1();mundur();set2();
}
//== servo_tengah ========================================================================

void servo_tengah()
{
  myServo1.write(90);
  myServo2.write(90);
  myServo3.write(90);
  myServo4.write(90);
  myServo5.write(90);
  myServo6.write(90);
  myServo7.write(90);
  myServo8.write(90);

  int s11 = 90; // kaki kiri depan servo(1) 
  int s12 = 90; // kaki kiri atas  depan servo(2)
  int s21 = 90; // kaki kiri belakang servo(3)
  int s22 = 90; // kaki kiri belakang atas servo(4)
  int s31 = 90; // kaki kanan belakang servo(5)
  int s32 = 90; // kaki kanan belakang atas servo(6)
  int s41 = 90; // kaki kanan depan servo(7)
  int s42 = 90; // kaki kanan atas depan servo(8)

}



//== Srv ===================================================================================

void srv( int  p11, int p21, int p31, int p41, int p12, int p22, int p32, int p42, int sp1, int sp2, int sp3, int sp4)
{

  // p11: Front Left Pivot Servo
  // p21: Back Left Pivot Servo
  // p31: Back Right Pivot Servo
  // p41: Front Right Pivot Servo
  // p12: Front Left Lift Servo
  // p22: Back Left Lift Servo
  // p32: Back Right Lift Servo
  // p42: Front Right Lift Servo
  // sp1: Speed 1
  // sp2: Speed 2
  // sp3: Speed 3
  // sp4: Speed 4

  // Multiply lift servo positions by manual height adjustment
  p12 = p12 + high * 3;
  p22 = p22 + high * 3;
  p32 = p32 + high * 3;
  p42 = p42 + high * 3;

  while ((s11 != p11) || (s21 != p21) || (s31 != p31) || (s41 != p41) || (s12 != p12) || (s22 != p22) || (s32 != p32) || (s42 != p42))
  {

    // Front Left Pivot Servo
    if (s11 < p11)            // if servo position is less than programmed position
    {
      if ((s11 + sp1) <= p11)
        s11 = s11 + sp1;      // set servo position equal to servo position plus speed constant
      else
        s11 = p11;
    }

    if (s11 > p11)            // if servo position is greater than programmed position
    {
      if ((s11 - sp1) >= p11)
        s11 = s11 - sp1;      // set servo position equal to servo position minus speed constant
      else
        s11 = p11;
    }

    // Back Left Pivot Servo
    if (s21 < p21)
    {
      if ((s21 + sp2) <= p21)
        s21 = s21 + sp2;
      else
        s21 = p21;
    }

    if (s21 > p21)
    {
      if ((s21 - sp2) >= p21)
        s21 = s21 - sp2;
      else
        s21 = p21;
    }

    // Back Right Pivot Servo
    if (s31 < p31)
    {
      if ((s31 + sp3) <= p31)
        s31 = s31 + sp3;
      else
        s31 = p31;
    }

    if (s31 > p31)
    {
      if ((s31 - sp3) >= p31)
        s31 = s31 - sp3;
      else
        s31 = p31;
    }

    // Front Right Pivot Servo
    if (s41 < p41)
    {
      if ((s41 + sp4) <= p41)
        s41 = s41 + sp4;
      else
        s41 = p41;
    }

    if (s41 > p41)
    {
      if ((s41 - sp4) >= p41)
        s41 = s41 - sp4;
      else
        s41 = p41;
    }

    // Front Left Lift Servo
    if (s12 < p12)
    {
      if ((s12 + sp1) <= p12)
        s12 = s12 + sp1;
      else
        s12 = p12;
    }

    if (s12 > p12)
    {
      if ((s12 - sp1) >= p12)
        s12 = s12 - sp1;
      else
        s12 = p12;
    }

    // Back Left Lift Servo
    if (s22 < p22)
    {
      if ((s22 + sp2) <= p22)
        s22 = s22 + sp2;
      else
        s22 = p22;
    }

    if (s22 > p22)
    {
      if ((s22 - sp2) >= p22)
        s22 = s22 - sp2;
      else
        s22 = p22;
    }

    // Back Right Lift Servo
    if (s32 < p32)
    {
      if ((s32 + sp3) <= p32)
        s32 = s32 + sp3;
      else
        s32 = p32;
    }

    if (s32 > p32)
    {
      if ((s32 - sp3) >= p32)
        s32 = s32 - sp3;
      else
        s32 = p32;
    }

    // Front Right Lift Servo
    if (s42 < p42)
    {
      if ((s42 + sp4) <= p42)
        s42 = s42 + sp4;
      else
        s42 = p42;
    }

    if (s42 > p42)
    {
      if ((s42 - sp4) >= p42)
        s42 = s42 - sp4;
      else
        s42 = p42;
    }

    // Write Pivot Servo Values
    myServo1.write(s11 + da);
    myServo3.write(s21 + db);
    myServo5.write(s31 + dc);
    myServo7.write(s41 + dd);

    // Write Lift Servos Values
    myServo2.write(s12);
    myServo4.write(s22);
    myServo6.write(s32);
    myServo8.write(s42);

    delay(spd); // Delay before next movement

  }
}
