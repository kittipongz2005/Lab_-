const int DG[2] = {27, 14};
const int segMentPin[7] = {4, 0, 17, 16, 23, 19, 18};
const int dot = 20;
int i;
int digit = 0;   
int num = 8;  // กำหนดค่าคงที่ให้แสดง "86" ตลอด

bool segMent[10][7] = {
  {1,1,1,1,1,1,0},  // 0
  {0,1,1,0,0,0,0},  // 1
  {1,1,0,1,1,0,1},  // 2
  {1,1,1,1,0,0,1},  // 3
  {0,1,1,0,0,1,1},  // 4
  {1,0,1,1,0,1,1},  // 5
  {1,0,1,1,1,1,1},  // 6
  {1,1,1,0,0,0,0},  // 7
  {1,1,1,1,1,1,1},  // 8
  {1,1,1,1,0,1,1}   // 9
};

hw_timer_t * timer = NULL;  /* create a hardware timer */

void IRAM_ATTR onTimer() {
  if (digit == 0) {
    digitalWrite(DG[0], LOW);  // เปิดหลักสิบ
    for (i = 0; i < 7; i++) {
      digitalWrite(segMentPin[i], segMent[2][i]);  // แสดงเลข 2
    }
    digitalWrite(DG[1], HIGH); // ปิดหลักหน่วย
    digit = 1;
  } else {
    digitalWrite(DG[1], LOW);  // เปิดหลักหน่วย
    for (i = 0; i < 7; i++) {
      digitalWrite(segMentPin[i], segMent[8][i]);  // แสดงเลข 8
    }
    digitalWrite(DG[0], HIGH); // ปิดหลักสิบ
    digit = 0;
  }
}

void setup() {
   timer = timerBegin(0, 80, true);   // Timer 0
   timerAttachInterrupt(timer, &onTimer, true);
   timerAlarmWrite(timer, 1000000 / 30 / 2, true);
   timerAlarmEnable(timer);
   
   for (i = 0; i < 2; i++) {
    pinMode(DG[i], OUTPUT);   
    digitalWrite(DG[i], HIGH);
  }  
  for (i = 0; i < 7; i++) {
    pinMode(segMentPin[i], OUTPUT);
    digitalWrite(segMentPin[i], HIGH);
  }  
}

void loop() {  
}