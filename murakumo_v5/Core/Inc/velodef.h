/*
 * 操作方法
 *
 * キャリブレーション
 * 1. ロータリスイッチゼロで Reset
 * 2. 置いて Enter
 *
 * 探索走行
 * 1. ロータリスイッチイチで Reset
 * 2. ロータリスイッチを 8 あたりに回す（ゲインを決定）
 * 3. 置いて Enter
 *
 * 二次走行
 * 1. ロータリスイッチニ で Reset
 * 2. ロータリスイッチを 8 あたりに回す（ゲインを決定）
 * 3. 置いて Enter
 *
 *
 * 機能
 * 左マーカ記憶
 * 「早い」と「遅い」の二値
 *
 */

#define PLAY 1

#define D_ANALOG 0
#define D_ANALOGRATE 0
#define D_MOTOR 0
#define D_SIDESENS 0	//
#define D_ENCODER 1	// Debug Encoder
#define D_PWM 0
#define D_ROTARY 0
#define D_PLAYMODE 0
#define D_SWITCH 0
#define D_IMU 1
#define D_FLASH 1
#define D_LED 0
#define D_VELOCITY_CONTROL 0
#define D_VELOCITY_CONTROL_TIMER 0
#define D_MATH 0
#define D_SLOWSTART 0
#define D_SEARCH 1
#define D_WHILE_PRINT 0
#define D_COURSE_SAVING 0

#define USE_ANALOG 1
#define USE_MOTOR 1
#define USE_SIDESENSOR 1	// Use SideSensor
#define USE_ENCODER 1
#define USE_ROTARY 1
#define USE_SWITCH 1
#define USE_LED 1
#define USE_FLASH 1
#define USE_IMU 1
#define USE_BUZZER 0
#define USE_VELOCITY_CONTROL 1
#define USE_SIGMOID_TRACE 0
#define USE_DANGERSTOP 0
#define USE_LR_DIFFERENCE 1
#define USE_PID_ARRAY 1
#define USE_COURSE_STATE_TIME 1

#define USE_SLOWSTART 1
#define USE_WRITE_FLASH 1

// one side only
#define LENGTH_SAMPLING 0
#define LEFTMARKER_SAMPLING 1

#define NOISY 0
#define GOD 0
#define P_ONLY 0

#if USE_PID_ARRAY

#define VELOCITY_TARGET_LOW 1000
#define VELOCITY_TARGET_HIGH 1500
#define VELOCITY_TARGET_MAX 2000

// 6 0.06
#define VKP 6
#define VKI 0.06f
// #define VKP 0.5f
// #define VKI 0.005f

// low speed
#define KP_LOW 17.5f
#define KP_LOW_TOLERANCE 0
#define KD_LOW 335.71f
#define KD_LOW_TOLERANCE ((635.71f - 335) / 16)
#define KI_LOW 0
#define KI_LOW_TOLERANCE 0

// high speed
#define KP_HIGH 25.5f
#define KP_HIGH_TOLERANCE ((41.5f - 25.5f) / 15)
#define KD_HIGH 335.71f
#define KD_HIGH_TOLERANCE ((395.71f - 25.5f) / 15)
#define KI_HIGH 0
#define KI_HIGH_TOLERANCE 0
/*
#define KP_HIGH 17.5f
#define KP_HIGH_TOLERANCE 2
#define KD_HIGH 335.71f
#define KD_HIGH_TOLERANCE 10
#define KI_HIGH 0
#define KI_HIGH_TOLERANCE 0
*/

#define KP_MAX 50
#define KP_MAX_TOLERANCE 0
#define KD_MAX 400
#define KD_MAX_TOLERANCE 13
#define KI_MAX 0
#define KI_MAX_TOLERANCE 0

#else

#if !USE_VELOCITY_CONTROL
#define COMMONSPEED0 0
#define COMMONSPEED1 100	// 700 // 570
#define COMMONSPEED2 100
#define COMMONSPEED3 100
#define COMMONSPEED4 100
#define COMMONSPEED5 100
#define COMMONSPEED6 100
#define COMMONSPEED7 100
#define COMMONSPEED8 100
#define COMMONSPEED9 100
#define COMMONSPEEDA 100	// 700 // 570
#define COMMONSPEEDB 100
#define COMMONSPEEDC 100
#define COMMONSPEEDD 100
#define COMMONSPEEDE 100
#define COMMONSPEEDF 100
#else
#define VELOCITY_TARGET0 1000
#define VELOCITY_TARGET1 1000
#define VELOCITY_TARGET2 1000
#define VELOCITY_TARGET3 1000
#define VELOCITY_TARGET4 1000
#define VELOCITY_TARGET5 1000
#define VELOCITY_TARGET6 1000
#define VELOCITY_TARGET7 1000
#define VELOCITY_TARGET8 1000
#define VELOCITY_TARGET9 1000
#define VELOCITY_TARGETA 1000
#define VELOCITY_TARGETB 1000
#define VELOCITY_TARGETC 1000
#define VELOCITY_TARGETD 1000
#define VELOCITY_TARGETE 1000
#define VELOCITY_TARGETF 1000
#endif

#if !NOISY
#define KP0 5.4f
#define KD0 200
#define KI0 0
#define KP1 5.4f
#define KD1 206.67f
#define KI1 0
#define KP2 5.4f
#define KD2 213.33f
#define KI2 0
#define KP3 5.4f
#define KD3 220
#define KI3 0
#define KP4 5.4f
#define KD4 226.67f
#define KI4 0
#define KP5 5.4f
#define KD5 233.33f
#define KI5 0
#define KP6 5.4f
#define KD6 240
#define KI6 0
#define KP7 5.4f
#define KD7 246.67f
#define KI7 0
#define KP8 5.4f
#define KD8 253.33f
#define KI8 0
#define KP9 5.4f
#define KD9 260
#define KI9 0
#define KPA 5.4f
#define KDA 266.67f
#define KIA 0
#define KPB 5.4f
#define KDB 273.33f
#define KIB 0
#define KPC 5.4f
#define KDC 280
#define KIC 0
#define KPD 5.4f
#define KDD 286.67f
#define KID 0
#define KPE 5.4f
#define KDE 293.33f
#define KIE 0
#define KPF 5.4f
#define KDF 300
#define KIF 0
#endif

#if P_ONLY
#define KP0 0
#define KP0 0
#define KI0 0
#define KP1 5.3f
#define KD1 0
#define KI1 0
#define KP2 5.37f
#define KD2 0
#define KI2 0
#define KP3 5.44f
#define KD3 0
#define KI3 0
#define KP4 5.51f
#define KD4 0
#define KI4 0
#define KP5 5.59f
#define KD5 0
#define KI5 0
#define KP6 5.66f
#define KD6 0
#define KI6 0
#define KP7 5.73f
#define KD7 0
#define KI7 0
#define KP8 5.8f
#define KD8 0
#define KI8 0
#define KP9 5.87f
#define KD9 0
#define KI9 0
#define KPA 5.94f
#define KDA 0
#define KIA 0
#define KPB 6.01f
#define KDB 0
#define KIB 0
#define KPC 6.09f
#define KDC 0
#define KIC 0
#define KPD 6.16f
#define KDD 0
#define KID 0
#define KPE 6.23f
#define KDE 0
#define KIE 0
#define KPF 6.3f
#define KDF 0
#define KIF 0
#endif

/*
 *
 * good parameters
 *
 * 500, 6.4, 13.75, 0
 * 750, 7.68, 16.5, 0
 *
 */

/*
#define KP1 2.8f	// 30 // 25
#define KD1 0	// 8  // 10
#define KI1 0	// 0.0005f
#define KP2 2.8f
#define KD2 3.4f
#define KI2 0

// god pid
#define VELOCITY_TARGET4 1000
#define KP4 17.5f
#define KD4 400
#define KI4 0

*/
// 5.46f == KP ... great!, 165.71 <= KD <= 170 ... great!

#if NOISY
#define KP0 17.5f
#define KD0 335
#define KI0 0
#define KP1 17.5f
#define KD1 335.71f
#define KI1 0
#define KP2 17.5f
#define KD2 357.14f
#define KI2 0
#define KP3 17.5f
#define KD3 378.57f
#define KI3 0
#define KP4 17.5f
#define KD4 400
#define KI4 0
#define KP5 17.5f
#define KD5 421.42f
#define KI5 0
#define KP6 17.5f
#define KD6 442.85f
#define KI6 0
#define KP7 17.5f
#define KD7 464.28f
#define KI7 0
#define KP8 17.5f
#define KD8 485.71f
#define KI8 0
#define KP9 17.5f
#define KD9 507.14f
#define KI9 0
#define KPA 17.5f
#define KDA 528.57f
#define KIA 0
#define KPB 17.5f
#define KDB 550
#define KIB 0
#define KPC 17.5f
#define KDC 571.42f
#define KIC 0
#define KPD 17.5f
#define KDD 592.85f
#define KID 0
#define KPE 17.5f
#define KDE 614.28f
#define KIE 0
#define KPF 17.5f
#define KDF 635.71f
#define KIF 0
#endif
#endif	// !USE_PID_ARRAY
