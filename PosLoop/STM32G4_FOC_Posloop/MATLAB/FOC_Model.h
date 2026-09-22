/*
 * File: FOC_Model.h
 *
 * Code generated for Simulink model 'FOC_Model'.
 *
 * Model version                  : 5.1
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Mon Jan 19 22:13:03 2026
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
  real_T SpeedReset;                   /* '<S3>/Chart' */
  real32_T Merge;                      /* '<S3>/Merge' */
  real32_T Merge2;                     /* '<S3>/Merge2' */
  real32_T Merge1;                     /* '<S3>/Merge1' */
  real32_T Saturation_j;               /* '<S209>/Saturation' */
  real32_T Integrator_DSTATE;          /* '<S100>/Integrator' */
  real32_T Integrator_DSTATE_b;        /* '<S150>/Integrator' */
  real32_T UnitDelay_DSTATE_g;         /* '<S168>/Unit Delay' */
  real32_T Integrator_DSTATE_h;        /* '<S202>/Integrator' */
  real32_T Integrator_PREV_U;          /* '<S202>/Integrator' */
  uint32_T speedloop_PREV_T;           /* '<S1>/speedloop' */
  uint16_T temporalCounter_i1;         /* '<S3>/Chart' */
  int8_T Integrator_PrevResetState;    /* '<S202>/Integrator' */
  uint8_T is_active_c3_FOC_Model;      /* '<S3>/Chart' */
  uint8_T is_c3_FOC_Model;             /* '<S3>/Chart' */
  uint8_T Integrator_SYSTEM_ENABLE;    /* '<S202>/Integrator' */
  boolean_T speedloop_RESET_ELAPS_T;   /* '<S1>/speedloop' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T ia;                         /* '<Root>/ia' */
  real32_T ib;                         /* '<Root>/ib' */
  real32_T ic;                         /* '<Root>/ic' */
  real32_T v_bus;                      /* '<Root>/v_bus' */
  real32_T Motor_OnOff;                /* '<Root>/Motor_OnOff' */
  real32_T Encoder_Theta;              /* '<Root>/Encoder_Theta' */
  real32_T Encoder_Cnt;                /* '<Root>/Encoder_Cnt' */
  real32_T PosRef;                     /* '<Root>/PosRef' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T tABC[3];                    /* '<Root>/tABC' */
} ExtY;

/* Type definition for custom storage class: Struct */
typedef struct CurrKPKI_tag {
  real32_T CurrKi;                     /* Referenced by:
                                        * '<S62>/Constant2'
                                        * '<S62>/Constant4'
                                        */
  real32_T CurrKp;                     /* Referenced by:
                                        * '<S62>/Constant1'
                                        * '<S62>/Constant3'
                                        */
} CurrKPKI_type;

typedef struct Pos_kpkikd_tag {
  real32_T Pos_kp;                     /* Referenced by: '<S2>/Constant' */
} Pos_kpkikd_type;

typedef struct motor_tag {
  real32_T Pn;                         /* Referenced by: '<S168>/Gain' */
} motor_type;

typedef struct spd_kpki_tag {
  real32_T spd_ki;                   /* Referenced by: '<S199>/Integral Gain' */
  real32_T spd_kp;               /* Referenced by: '<S207>/Proportional Gain' */
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
extern real32_T Motor_state;           /* '<S3>/Chart' */
extern real32_T PosFd;                 /* '<S2>/Add' */
extern real32_T SpeedFd;               /* '<S168>/Gain' */

/* Model entry point functions */
extern void FOC_Model_initialize(void);
extern void FOC_Model_step(void);

/* Exported data declaration */

/* Declaration for custom storage class: Struct */
extern CurrKPKI_type CurrKPKI;
extern Pos_kpkikd_type Pos_kpkikd;
extern motor_type motor;
extern spd_kpki_type spd_kpki;

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S62>/Scope' : Unused code path elimination
 * Block '<S3>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S3>/Data Type Conversion4' : Eliminate redundant data type conversion
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
 * hilite_system('speedloop/FOC_Model')    - opens subsystem speedloop/FOC_Model
 * hilite_system('speedloop/FOC_Model/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'speedloop'
 * '<S1>'   : 'speedloop/FOC_Model'
 * '<S2>'   : 'speedloop/FOC_Model/Pos_Loop'
 * '<S3>'   : 'speedloop/FOC_Model/currloop'
 * '<S4>'   : 'speedloop/FOC_Model/speedloop'
 * '<S5>'   : 'speedloop/FOC_Model/Pos_Loop/PID Controller'
 * '<S6>'   : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Anti-windup'
 * '<S7>'   : 'speedloop/FOC_Model/Pos_Loop/PID Controller/D Gain'
 * '<S8>'   : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Filter'
 * '<S9>'   : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Filter ICs'
 * '<S10>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/I Gain'
 * '<S11>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Ideal P Gain'
 * '<S12>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Ideal P Gain Fdbk'
 * '<S13>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Integrator'
 * '<S14>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Integrator ICs'
 * '<S15>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/N Copy'
 * '<S16>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/N Gain'
 * '<S17>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/P Copy'
 * '<S18>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Parallel P Gain'
 * '<S19>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Reset Signal'
 * '<S20>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Saturation'
 * '<S21>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Saturation Fdbk'
 * '<S22>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Sum'
 * '<S23>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Sum Fdbk'
 * '<S24>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Tracking Mode'
 * '<S25>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Tracking Mode Sum'
 * '<S26>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Tsamp - Integral'
 * '<S27>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Tsamp - Ngain'
 * '<S28>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/postSat Signal'
 * '<S29>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/preSat Signal'
 * '<S30>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Anti-windup/Disabled'
 * '<S31>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/D Gain/Disabled'
 * '<S32>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Filter/Disabled'
 * '<S33>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Filter ICs/Disabled'
 * '<S34>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/I Gain/Disabled'
 * '<S35>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Ideal P Gain/Passthrough'
 * '<S36>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S37>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Integrator/Disabled'
 * '<S38>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Integrator ICs/Disabled'
 * '<S39>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S40>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/N Gain/Disabled'
 * '<S41>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/P Copy/Disabled'
 * '<S42>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Parallel P Gain/External Parameters'
 * '<S43>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Reset Signal/Disabled'
 * '<S44>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Saturation/Enabled'
 * '<S45>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Saturation Fdbk/Disabled'
 * '<S46>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Sum/Passthrough_P'
 * '<S47>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Sum Fdbk/Disabled'
 * '<S48>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Tracking Mode/Disabled'
 * '<S49>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S50>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S51>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S52>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/postSat Signal/Forward_Path'
 * '<S53>'  : 'speedloop/FOC_Model/Pos_Loop/PID Controller/preSat Signal/Forward_Path'
 * '<S54>'  : 'speedloop/FOC_Model/currloop/AntiPark'
 * '<S55>'  : 'speedloop/FOC_Model/currloop/Chart'
 * '<S56>'  : 'speedloop/FOC_Model/currloop/Clark'
 * '<S57>'  : 'speedloop/FOC_Model/currloop/If Action Subsystem'
 * '<S58>'  : 'speedloop/FOC_Model/currloop/If Action Subsystem1'
 * '<S59>'  : 'speedloop/FOC_Model/currloop/If Action Subsystem2'
 * '<S60>'  : 'speedloop/FOC_Model/currloop/Park'
 * '<S61>'  : 'speedloop/FOC_Model/currloop/SVPWM'
 * '<S62>'  : 'speedloop/FOC_Model/currloop/idq_Controller'
 * '<S63>'  : 'speedloop/FOC_Model/currloop/SVPWM/AntiClark'
 * '<S64>'  : 'speedloop/FOC_Model/currloop/SVPWM/ei_t'
 * '<S65>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1'
 * '<S66>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2'
 * '<S67>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Anti-windup'
 * '<S68>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/D Gain'
 * '<S69>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Filter'
 * '<S70>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Filter ICs'
 * '<S71>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/I Gain'
 * '<S72>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Ideal P Gain'
 * '<S73>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Ideal P Gain Fdbk'
 * '<S74>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Integrator'
 * '<S75>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Integrator ICs'
 * '<S76>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/N Copy'
 * '<S77>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/N Gain'
 * '<S78>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/P Copy'
 * '<S79>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Parallel P Gain'
 * '<S80>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Reset Signal'
 * '<S81>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Saturation'
 * '<S82>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Saturation Fdbk'
 * '<S83>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Sum'
 * '<S84>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Sum Fdbk'
 * '<S85>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tracking Mode'
 * '<S86>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tracking Mode Sum'
 * '<S87>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tsamp - Integral'
 * '<S88>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tsamp - Ngain'
 * '<S89>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/postSat Signal'
 * '<S90>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/preSat Signal'
 * '<S91>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel'
 * '<S92>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S93>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S94>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/D Gain/Disabled'
 * '<S95>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Filter/Disabled'
 * '<S96>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Filter ICs/Disabled'
 * '<S97>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/I Gain/External Parameters'
 * '<S98>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Ideal P Gain/Passthrough'
 * '<S99>'  : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S100>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Integrator/Discrete'
 * '<S101>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Integrator ICs/Internal IC'
 * '<S102>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S103>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/N Gain/Disabled'
 * '<S104>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/P Copy/Disabled'
 * '<S105>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Parallel P Gain/External Parameters'
 * '<S106>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Reset Signal/Disabled'
 * '<S107>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Saturation/Enabled'
 * '<S108>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Saturation Fdbk/Disabled'
 * '<S109>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Sum/Sum_PI'
 * '<S110>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Sum Fdbk/Disabled'
 * '<S111>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tracking Mode/Disabled'
 * '<S112>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S113>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S114>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S115>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/postSat Signal/Forward_Path'
 * '<S116>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller1/preSat Signal/Forward_Path'
 * '<S117>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Anti-windup'
 * '<S118>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/D Gain'
 * '<S119>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Filter'
 * '<S120>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Filter ICs'
 * '<S121>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/I Gain'
 * '<S122>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Ideal P Gain'
 * '<S123>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Ideal P Gain Fdbk'
 * '<S124>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Integrator'
 * '<S125>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Integrator ICs'
 * '<S126>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/N Copy'
 * '<S127>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/N Gain'
 * '<S128>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/P Copy'
 * '<S129>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Parallel P Gain'
 * '<S130>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Reset Signal'
 * '<S131>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Saturation'
 * '<S132>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Saturation Fdbk'
 * '<S133>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Sum'
 * '<S134>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Sum Fdbk'
 * '<S135>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tracking Mode'
 * '<S136>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tracking Mode Sum'
 * '<S137>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tsamp - Integral'
 * '<S138>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tsamp - Ngain'
 * '<S139>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/postSat Signal'
 * '<S140>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/preSat Signal'
 * '<S141>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel'
 * '<S142>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S143>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S144>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/D Gain/Disabled'
 * '<S145>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Filter/Disabled'
 * '<S146>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Filter ICs/Disabled'
 * '<S147>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/I Gain/External Parameters'
 * '<S148>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Ideal P Gain/Passthrough'
 * '<S149>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Ideal P Gain Fdbk/Disabled'
 * '<S150>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Integrator/Discrete'
 * '<S151>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Integrator ICs/Internal IC'
 * '<S152>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/N Copy/Disabled wSignal Specification'
 * '<S153>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/N Gain/Disabled'
 * '<S154>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/P Copy/Disabled'
 * '<S155>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Parallel P Gain/External Parameters'
 * '<S156>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Reset Signal/Disabled'
 * '<S157>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Saturation/Enabled'
 * '<S158>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Saturation Fdbk/Disabled'
 * '<S159>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Sum/Sum_PI'
 * '<S160>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Sum Fdbk/Disabled'
 * '<S161>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tracking Mode/Disabled'
 * '<S162>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tracking Mode Sum/Passthrough'
 * '<S163>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tsamp - Integral/TsSignalSpecification'
 * '<S164>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/Tsamp - Ngain/Passthrough'
 * '<S165>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/postSat Signal/Forward_Path'
 * '<S166>' : 'speedloop/FOC_Model/currloop/idq_Controller/PID Controller2/preSat Signal/Forward_Path'
 * '<S167>' : 'speedloop/FOC_Model/speedloop/PID Controller3'
 * '<S168>' : 'speedloop/FOC_Model/speedloop/ThetaToSpeed'
 * '<S169>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Anti-windup'
 * '<S170>' : 'speedloop/FOC_Model/speedloop/PID Controller3/D Gain'
 * '<S171>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Filter'
 * '<S172>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Filter ICs'
 * '<S173>' : 'speedloop/FOC_Model/speedloop/PID Controller3/I Gain'
 * '<S174>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Ideal P Gain'
 * '<S175>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Ideal P Gain Fdbk'
 * '<S176>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Integrator'
 * '<S177>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Integrator ICs'
 * '<S178>' : 'speedloop/FOC_Model/speedloop/PID Controller3/N Copy'
 * '<S179>' : 'speedloop/FOC_Model/speedloop/PID Controller3/N Gain'
 * '<S180>' : 'speedloop/FOC_Model/speedloop/PID Controller3/P Copy'
 * '<S181>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Parallel P Gain'
 * '<S182>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Reset Signal'
 * '<S183>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Saturation'
 * '<S184>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Saturation Fdbk'
 * '<S185>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Sum'
 * '<S186>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Sum Fdbk'
 * '<S187>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Tracking Mode'
 * '<S188>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Tracking Mode Sum'
 * '<S189>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Tsamp - Integral'
 * '<S190>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Tsamp - Ngain'
 * '<S191>' : 'speedloop/FOC_Model/speedloop/PID Controller3/postSat Signal'
 * '<S192>' : 'speedloop/FOC_Model/speedloop/PID Controller3/preSat Signal'
 * '<S193>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Anti-windup/Disc. Clamping Parallel'
 * '<S194>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S195>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S196>' : 'speedloop/FOC_Model/speedloop/PID Controller3/D Gain/Disabled'
 * '<S197>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Filter/Disabled'
 * '<S198>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Filter ICs/Disabled'
 * '<S199>' : 'speedloop/FOC_Model/speedloop/PID Controller3/I Gain/Internal Parameters'
 * '<S200>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Ideal P Gain/Passthrough'
 * '<S201>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Ideal P Gain Fdbk/Disabled'
 * '<S202>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Integrator/Discrete'
 * '<S203>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Integrator ICs/Internal IC'
 * '<S204>' : 'speedloop/FOC_Model/speedloop/PID Controller3/N Copy/Disabled wSignal Specification'
 * '<S205>' : 'speedloop/FOC_Model/speedloop/PID Controller3/N Gain/Disabled'
 * '<S206>' : 'speedloop/FOC_Model/speedloop/PID Controller3/P Copy/Disabled'
 * '<S207>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Parallel P Gain/Internal Parameters'
 * '<S208>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Reset Signal/External Reset'
 * '<S209>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Saturation/Enabled'
 * '<S210>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Saturation Fdbk/Disabled'
 * '<S211>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Sum/Sum_PI'
 * '<S212>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Sum Fdbk/Disabled'
 * '<S213>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Tracking Mode/Disabled'
 * '<S214>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Tracking Mode Sum/Passthrough'
 * '<S215>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Tsamp - Integral/TsSignalSpecification'
 * '<S216>' : 'speedloop/FOC_Model/speedloop/PID Controller3/Tsamp - Ngain/Passthrough'
 * '<S217>' : 'speedloop/FOC_Model/speedloop/PID Controller3/postSat Signal/Forward_Path'
 * '<S218>' : 'speedloop/FOC_Model/speedloop/PID Controller3/preSat Signal/Forward_Path'
 * '<S219>' : 'speedloop/FOC_Model/speedloop/ThetaToSpeed/Angle_Limit'
 * '<S220>' : 'speedloop/FOC_Model/speedloop/ThetaToSpeed/Angle_Limit/If Action Subsystem1'
 * '<S221>' : 'speedloop/FOC_Model/speedloop/ThetaToSpeed/Angle_Limit/If Action Subsystem2'
 * '<S222>' : 'speedloop/FOC_Model/speedloop/ThetaToSpeed/Angle_Limit/If Action Subsystem3'
 */
#endif                                 /* RTW_HEADER_FOC_Model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
