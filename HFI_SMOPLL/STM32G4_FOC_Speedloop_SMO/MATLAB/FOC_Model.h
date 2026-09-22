/*
 * File: FOC_Model.h
 *
 * Code generated for Simulink model 'FOC_Model'.
 *
 * Model version                  : 5.6
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sun Jan 25 19:34:16 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FOC_Model_h_
#define RTW_HEADER_FOC_Model_h_
#ifndef FOC_Model_COMMON_INCLUDES_
#define FOC_Model_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_Model_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T ZReset;                       /* '<S2>/Chart1' */
  real_T SpeedReset;                   /* '<S2>/Chart1' */
  real32_T Merge5;                     /* '<S2>/Merge5' */
  real32_T Merge3;                     /* '<S2>/Merge3' */
  real32_T Merge4;                     /* '<S2>/Merge4' */
  real32_T Saturation;                 /* '<S220>/Saturation' */
  real32_T UnitDelay_DSTATE_m;         /* '<S19>/Unit Delay' */
  real32_T Integrator_DSTATE;          /* '<S111>/Integrator' */
  real32_T Integrator_DSTATE_b;        /* '<S161>/Integrator' */
  real32_T Delay_DSTATE;               /* '<S12>/Delay' */
  real32_T UnitDelay2_DSTATE;          /* '<S17>/Unit Delay2' */
  real32_T UnitDelay3_DSTATE;          /* '<S17>/Unit Delay3' */
  real32_T UnitDelay4_DSTATE;          /* '<S17>/Unit Delay4' */
  real32_T UnitDelay5_DSTATE;          /* '<S17>/Unit Delay5' */
  real32_T Integrator_DSTATE_o;        /* '<S53>/Integrator' */
  real32_T Delay_DSTATE_j;             /* '<S15>/Delay' */
  real32_T UnitDelay_DSTATE_e;         /* '<S17>/Unit Delay' */
  real32_T UnitDelay1_DSTATE_j;        /* '<S17>/Unit Delay1' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S9>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S9>/Discrete-Time Integrator1' */
  real32_T Integrator_DSTATE_h;        /* '<S213>/Integrator' */
  real32_T UnitDelay_DSTATE_g;         /* '<S179>/Unit Delay' */
  real32_T Integrator_PREV_U;          /* '<S213>/Integrator' */
  uint32_T speedloop_PREV_T;           /* '<S1>/speedloop' */
  uint16_T temporalCounter_i1;         /* '<S2>/Chart1' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S9>/Discrete-Time Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S9>/Discrete-Time Integrator1' */
  int8_T Integrator_PrevResetState;    /* '<S213>/Integrator' */
  uint8_T is_active_c1_FOC_Model;      /* '<S2>/Chart1' */
  uint8_T is_c1_FOC_Model;             /* '<S2>/Chart1' */
  uint8_T Integrator_SYSTEM_ENABLE;    /* '<S213>/Integrator' */
  boolean_T speedloop_RESET_ELAPS_T;   /* '<S1>/speedloop' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T ia;                         /* '<Root>/ia' */
  real32_T ib;                         /* '<Root>/ib' */
  real32_T ic;                         /* '<Root>/ic' */
  real32_T v_bus;                      /* '<Root>/v_bus' */
  real32_T Motor_OnOff;                /* '<Root>/Motor_OnOff' */
  real32_T SpeedRef;                   /* '<Root>/SpeedRef' */
  real32_T Encoder_Theta;              /* '<Root>/Encoder_Theta' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T tABC[3];                    /* '<Root>/tABC' */
} ExtY;

/* Type definition for custom storage class: Struct */
typedef struct CurrKPKI_tag {
  real32_T CurrKi;                     /* Referenced by:
                                        * '<S14>/Constant2'
                                        * '<S14>/Constant4'
                                        */
  real32_T CurrKp;                     /* Referenced by:
                                        * '<S14>/Constant1'
                                        * '<S14>/Constant3'
                                        */
} CurrKPKI_type;

typedef struct ObGain_tag {
  real32_T GainK;                      /* Referenced by:
                                        * '<S17>/Gain21'
                                        * '<S17>/Gain23'
                                        */
  real32_T GainM;                      /* Referenced by:
                                        * '<S17>/Gain22'
                                        * '<S17>/Gain25'
                                        */
} ObGain_type;

typedef struct motor_tag {
  real32_T L;                          /* Referenced by:
                                        * '<S17>/Gain'
                                        * '<S17>/Gain15'
                                        * '<S17>/Gain16'
                                        * '<S17>/Gain17'
                                        * '<S17>/Gain18'
                                        * '<S17>/Gain19'
                                        */
  real32_T Pn;                         /* Referenced by:
                                        * '<S9>/Gain'
                                        * '<S12>/Gain'
                                        * '<S179>/Gain'
                                        */
  real32_T Rs;                         /* Referenced by:
                                        * '<S17>/Gain'
                                        * '<S17>/Gain17'
                                        */
} motor_type;

typedef struct spd_kpki_tag {
  real32_T spd_ki;                   /* Referenced by: '<S210>/Integral Gain' */
  real32_T spd_kp;               /* Referenced by: '<S218>/Proportional Gain' */
} spd_kpki_type;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick1;
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T SMO_Theta;             /* '<S19>/Unit Delay' */
extern real32_T SMO_Wm;                /* '<S12>/Gain1' */
extern real32_T Motor_state;           /* '<S2>/Chart1' */
extern real32_T SpeedFd;               /* '<S179>/Gain' */

/* Model entry point functions */
extern void FOC_Model_initialize(void);
extern void FOC_Model_step(void);

/* Exported data declaration */

/* Declaration for custom storage class: Struct */
extern CurrKPKI_type CurrKPKI;
extern ObGain_type ObGain;
extern motor_type motor;
extern spd_kpki_type spd_kpki;

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S12>/Scope' : Unused code path elimination
 * Block '<S12>/Scope1' : Unused code path elimination
 * Block '<S17>/Scope' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S14>/Scope' : Unused code path elimination
 * Block '<S2>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion4' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('SMO_Speedloop/FOC_Model')    - opens subsystem SMO_Speedloop/FOC_Model
 * hilite_system('SMO_Speedloop/FOC_Model/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SMO_Speedloop'
 * '<S1>'   : 'SMO_Speedloop/FOC_Model'
 * '<S2>'   : 'SMO_Speedloop/FOC_Model/currloop'
 * '<S3>'   : 'SMO_Speedloop/FOC_Model/speedloop'
 * '<S4>'   : 'SMO_Speedloop/FOC_Model/currloop/AntiPark'
 * '<S5>'   : 'SMO_Speedloop/FOC_Model/currloop/Chart1'
 * '<S6>'   : 'SMO_Speedloop/FOC_Model/currloop/Clark'
 * '<S7>'   : 'SMO_Speedloop/FOC_Model/currloop/If Action Subsystem3'
 * '<S8>'   : 'SMO_Speedloop/FOC_Model/currloop/If Action Subsystem4'
 * '<S9>'   : 'SMO_Speedloop/FOC_Model/currloop/If Action Subsystem5'
 * '<S10>'  : 'SMO_Speedloop/FOC_Model/currloop/If Action Subsystem6'
 * '<S11>'  : 'SMO_Speedloop/FOC_Model/currloop/Park'
 * '<S12>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO'
 * '<S13>'  : 'SMO_Speedloop/FOC_Model/currloop/SVPWM'
 * '<S14>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller'
 * '<S15>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/LPF1'
 * '<S16>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2'
 * '<S17>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/discrete smo '
 * '<S18>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller'
 * '<S19>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/SpeedToTheta'
 * '<S20>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Anti-windup'
 * '<S21>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/D Gain'
 * '<S22>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Filter'
 * '<S23>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Filter ICs'
 * '<S24>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/I Gain'
 * '<S25>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Ideal P Gain'
 * '<S26>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Ideal P Gain Fdbk'
 * '<S27>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Integrator'
 * '<S28>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Integrator ICs'
 * '<S29>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/N Copy'
 * '<S30>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/N Gain'
 * '<S31>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/P Copy'
 * '<S32>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Parallel P Gain'
 * '<S33>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Reset Signal'
 * '<S34>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Saturation'
 * '<S35>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Saturation Fdbk'
 * '<S36>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Sum'
 * '<S37>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Sum Fdbk'
 * '<S38>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Tracking Mode'
 * '<S39>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Tracking Mode Sum'
 * '<S40>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Tsamp - Integral'
 * '<S41>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Tsamp - Ngain'
 * '<S42>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/postSat Signal'
 * '<S43>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/preSat Signal'
 * '<S44>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S45>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S46>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S47>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/D Gain/Disabled'
 * '<S48>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Filter/Disabled'
 * '<S49>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Filter ICs/Disabled'
 * '<S50>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/I Gain/Internal Parameters'
 * '<S51>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Ideal P Gain/Passthrough'
 * '<S52>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S53>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Integrator/Discrete'
 * '<S54>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Integrator ICs/Internal IC'
 * '<S55>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S56>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/N Gain/Disabled'
 * '<S57>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/P Copy/Disabled'
 * '<S58>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S59>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Reset Signal/Disabled'
 * '<S60>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Saturation/Enabled'
 * '<S61>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Saturation Fdbk/Disabled'
 * '<S62>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Sum/Sum_PI'
 * '<S63>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Sum Fdbk/Disabled'
 * '<S64>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Tracking Mode/Disabled'
 * '<S65>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S66>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S67>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S68>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/postSat Signal/Forward_Path'
 * '<S69>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/PID Controller/preSat Signal/Forward_Path'
 * '<S70>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/SpeedToTheta/Angle_Limit'
 * '<S71>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/SpeedToTheta/Angle_Limit/If Action Subsystem1'
 * '<S72>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/SpeedToTheta/Angle_Limit/If Action Subsystem2'
 * '<S73>'  : 'SMO_Speedloop/FOC_Model/currloop/SMO/PLL2/SpeedToTheta/Angle_Limit/If Action Subsystem3'
 * '<S74>'  : 'SMO_Speedloop/FOC_Model/currloop/SVPWM/AntiClark'
 * '<S75>'  : 'SMO_Speedloop/FOC_Model/currloop/SVPWM/ei_t'
 * '<S76>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1'
 * '<S77>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2'
 * '<S78>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Anti-windup'
 * '<S79>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/D Gain'
 * '<S80>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Filter'
 * '<S81>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Filter ICs'
 * '<S82>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/I Gain'
 * '<S83>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Ideal P Gain'
 * '<S84>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Ideal P Gain Fdbk'
 * '<S85>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Integrator'
 * '<S86>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Integrator ICs'
 * '<S87>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/N Copy'
 * '<S88>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/N Gain'
 * '<S89>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/P Copy'
 * '<S90>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Parallel P Gain'
 * '<S91>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Reset Signal'
 * '<S92>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Saturation'
 * '<S93>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Saturation Fdbk'
 * '<S94>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Sum'
 * '<S95>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Sum Fdbk'
 * '<S96>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tracking Mode'
 * '<S97>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tracking Mode Sum'
 * '<S98>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tsamp - Integral'
 * '<S99>'  : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tsamp - Ngain'
 * '<S100>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/postSat Signal'
 * '<S101>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/preSat Signal'
 * '<S102>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S103>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S104>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S105>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/D Gain/Disabled'
 * '<S106>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Filter/Disabled'
 * '<S107>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Filter ICs/Disabled'
 * '<S108>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/I Gain/External Parameters'
 * '<S109>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Ideal P Gain/Passthrough'
 * '<S110>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S111>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Integrator/Discrete'
 * '<S112>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Integrator ICs/Internal IC'
 * '<S113>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S114>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/N Gain/Disabled'
 * '<S115>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/P Copy/Disabled'
 * '<S116>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Parallel P Gain/External Parameters'
 * '<S117>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Reset Signal/Disabled'
 * '<S118>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Saturation/Enabled'
 * '<S119>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Saturation Fdbk/Disabled'
 * '<S120>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Sum/Sum_PI'
 * '<S121>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Sum Fdbk/Disabled'
 * '<S122>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tracking Mode/Disabled'
 * '<S123>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S124>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S125>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S126>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/postSat Signal/Forward_Path'
 * '<S127>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/preSat Signal/Forward_Path'
 * '<S128>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Anti-windup'
 * '<S129>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/D Gain'
 * '<S130>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Filter'
 * '<S131>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Filter ICs'
 * '<S132>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/I Gain'
 * '<S133>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Ideal P Gain'
 * '<S134>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Ideal P Gain Fdbk'
 * '<S135>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Integrator'
 * '<S136>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Integrator ICs'
 * '<S137>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/N Copy'
 * '<S138>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/N Gain'
 * '<S139>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/P Copy'
 * '<S140>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Parallel P Gain'
 * '<S141>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Reset Signal'
 * '<S142>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Saturation'
 * '<S143>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Saturation Fdbk'
 * '<S144>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Sum'
 * '<S145>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Sum Fdbk'
 * '<S146>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tracking Mode'
 * '<S147>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tracking Mode Sum'
 * '<S148>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tsamp - Integral'
 * '<S149>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tsamp - Ngain'
 * '<S150>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/postSat Signal'
 * '<S151>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/preSat Signal'
 * '<S152>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel'
 * '<S153>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S154>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S155>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/D Gain/Disabled'
 * '<S156>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Filter/Disabled'
 * '<S157>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Filter ICs/Disabled'
 * '<S158>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/I Gain/External Parameters'
 * '<S159>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Ideal P Gain/Passthrough'
 * '<S160>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S161>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Integrator/Discrete'
 * '<S162>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Integrator ICs/Internal IC'
 * '<S163>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/N Copy/Disabled wSignal Specification'
 * '<S164>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/N Gain/Disabled'
 * '<S165>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/P Copy/Disabled'
 * '<S166>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Parallel P Gain/External Parameters'
 * '<S167>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Reset Signal/Disabled'
 * '<S168>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Saturation/Enabled'
 * '<S169>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Saturation Fdbk/Disabled'
 * '<S170>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Sum/Sum_PI'
 * '<S171>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Sum Fdbk/Disabled'
 * '<S172>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tracking Mode/Disabled'
 * '<S173>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S174>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tsamp - Integral/TsSignalSpecification'
 * '<S175>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S176>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/postSat Signal/Forward_Path'
 * '<S177>' : 'SMO_Speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/preSat Signal/Forward_Path'
 * '<S178>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3'
 * '<S179>' : 'SMO_Speedloop/FOC_Model/speedloop/ThetaToSpeed'
 * '<S180>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Anti-windup'
 * '<S181>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/D Gain'
 * '<S182>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Filter'
 * '<S183>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Filter ICs'
 * '<S184>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/I Gain'
 * '<S185>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Ideal P Gain'
 * '<S186>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Ideal P Gain Fdbk'
 * '<S187>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Integrator'
 * '<S188>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Integrator ICs'
 * '<S189>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/N Copy'
 * '<S190>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/N Gain'
 * '<S191>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/P Copy'
 * '<S192>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Parallel P Gain'
 * '<S193>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Reset Signal'
 * '<S194>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Saturation'
 * '<S195>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Saturation Fdbk'
 * '<S196>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Sum'
 * '<S197>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Sum Fdbk'
 * '<S198>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Tracking Mode'
 * '<S199>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Tracking Mode Sum'
 * '<S200>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Tsamp - Integral'
 * '<S201>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Tsamp - Ngain'
 * '<S202>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/postSat Signal'
 * '<S203>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/preSat Signal'
 * '<S204>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Anti-windup/Disc. Clamping Parallel'
 * '<S205>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S206>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S207>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/D Gain/Disabled'
 * '<S208>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Filter/Disabled'
 * '<S209>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Filter ICs/Disabled'
 * '<S210>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/I Gain/Internal Parameters'
 * '<S211>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Ideal P Gain/Passthrough'
 * '<S212>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Ideal P Gain Fdbk/Disabled'
 * '<S213>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Integrator/Discrete'
 * '<S214>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Integrator ICs/Internal IC'
 * '<S215>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/N Copy/Disabled wSignal Specification'
 * '<S216>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/N Gain/Disabled'
 * '<S217>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/P Copy/Disabled'
 * '<S218>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Parallel P Gain/Internal Parameters'
 * '<S219>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Reset Signal/External Reset'
 * '<S220>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Saturation/Enabled'
 * '<S221>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Saturation Fdbk/Disabled'
 * '<S222>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Sum/Sum_PI'
 * '<S223>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Sum Fdbk/Disabled'
 * '<S224>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Tracking Mode/Disabled'
 * '<S225>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Tracking Mode Sum/Passthrough'
 * '<S226>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Tsamp - Integral/TsSignalSpecification'
 * '<S227>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/Tsamp - Ngain/Passthrough'
 * '<S228>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/postSat Signal/Forward_Path'
 * '<S229>' : 'SMO_Speedloop/FOC_Model/speedloop/PID Controller3/preSat Signal/Forward_Path'
 * '<S230>' : 'SMO_Speedloop/FOC_Model/speedloop/ThetaToSpeed/Angle_Limit'
 * '<S231>' : 'SMO_Speedloop/FOC_Model/speedloop/ThetaToSpeed/Angle_Limit/If Action Subsystem1'
 * '<S232>' : 'SMO_Speedloop/FOC_Model/speedloop/ThetaToSpeed/Angle_Limit/If Action Subsystem2'
 * '<S233>' : 'SMO_Speedloop/FOC_Model/speedloop/ThetaToSpeed/Angle_Limit/If Action Subsystem3'
 */
#endif                                 /* RTW_HEADER_FOC_Model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
