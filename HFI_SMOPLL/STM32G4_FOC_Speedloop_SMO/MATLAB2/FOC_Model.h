/*
 * File: FOC_Model.h
 *
 * Code generated for Simulink model 'FOC_Model'.
 *
 * Model version                  : 6.168
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Sep 21 13:52:29 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef FOC_Model_h_
#define FOC_Model_h_
#ifndef FOC_Model_COMMON_INCLUDES_
#define FOC_Model_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
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
  real32_T Delay1_DSTATE[2];           /* '<S20>/Delay1' */
  real32_T Delay3_DSTATE[2];           /* '<S20>/Delay3' */
  real32_T Delay1_DSTATE_d[2];         /* '<S19>/Delay1' */
  real32_T Delay3_DSTATE_e[2];         /* '<S19>/Delay3' */
  real32_T DiscreteFilter3_states_d[2];/* '<S17>/Discrete Filter3' */
  real32_T Delay1_DSTATE_c[2];         /* '<S21>/Delay1' */
  real32_T RateTransition2;            /* '<S1>/Rate Transition2' */
  real32_T UD_DSTATE;                  /* '<S172>/UD' */
  real32_T Integrator_DSTATE;          /* '<S179>/Integrator' */
  real32_T PositiveResponseIntegrator_DSTA;/* '<S21>/PositiveResponseIntegrator' */
  real32_T NegativeResponseIntegrator_DSTA;/* '<S21>/NegativeResponseIntegrator' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S17>/Discrete-Time Integrator' */
  real32_T Delay_DSTATE;               /* '<S20>/Delay' */
  real32_T UnitDelay_DSTATE;           /* '<S4>/Unit Delay' */
  real32_T UnitDelay1_DSTATE;          /* '<S4>/Unit Delay1' */
  real32_T UnitDelay2_DSTATE;          /* '<S4>/Unit Delay2' */
  real32_T UnitDelay3_DSTATE;          /* '<S4>/Unit Delay3' */
  real32_T Delay2_DSTATE;              /* '<S20>/Delay2' */
  real32_T DiscreteTimeIntegrator_DSTATE_o;/* '<S10>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S11>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_m;/* '<S14>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_e;/* '<S15>/Discrete-Time Integrator' */
  real32_T DiscreteFilter3_states;     /* '<S15>/Discrete Filter3' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S15>/Discrete-Time Integrator1' */
  real32_T DiscreteFilter2_states;     /* '<S15>/Discrete Filter2' */
  real32_T Integrator_DSTATE_l;        /* '<S61>/Integrator' */
  real32_T Filter_DSTATE;              /* '<S56>/Filter' */
  real32_T DiscreteFilter5_states;     /* '<S4>/Discrete Filter5' */
  real32_T Delay4_DSTATE;              /* '<S19>/Delay4' */
  real32_T Delay_DSTATE_e;             /* '<S19>/Delay' */
  real32_T UnitDelay6_DSTATE;          /* '<S4>/Unit Delay6' */
  real32_T Delay6_DSTATE;              /* '<S19>/Delay6' */
  real32_T Delay2_DSTATE_o;            /* '<S19>/Delay2' */
  real32_T Integrator_DSTATE_j;        /* '<S115>/Integrator' */
  real32_T UD_DSTATE_n;                /* '<S108>/UD' */
  real32_T DiscreteFilter2_states_b;   /* '<S17>/Discrete Filter2' */
  real32_T Delay_DSTATE_m;             /* '<S21>/Delay' */
  real32_T RateTransition2_Buffer0;    /* '<S1>/Rate Transition2' */
  real32_T lambda_mem;                 /* '<S4>/MATLAB Function' */
  real32_T theta_prev;                 /* '<S4>/MATLAB Function' */
  real32_T dir_mem;                    /* '<S4>/DirectionLatch' */
  uint16_T enter_count;                /* '<S4>/MATLAB Function' */
  uint16_T exit_count;                 /* '<S4>/MATLAB Function' */
  uint16_T valid_count;                /* '<S4>/MATLAB Function' */
  uint16_T wake_count;                 /* '<S4>/MATLAB Function' */
  uint16_T positive_count;             /* '<S4>/DirectionLatch' */
  uint16_T negative_count;             /* '<S4>/DirectionLatch' */
  uint16_T count;                      /* '<S1>/StartupManager' */
  int8_T PositiveResponseIntegrator_Prev;/* '<S21>/PositiveResponseIntegrator' */
  int8_T NegativeResponseIntegrator_Prev;/* '<S21>/NegativeResponseIntegrator' */
  uint8_T Output_DSTATE;               /* '<S8>/Output' */
  uint8_T mode;                        /* '<S4>/MATLAB Function' */
  uint8_T state;                       /* '<S1>/StartupManager' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T ia;                         /* '<Root>/ia' */
  real32_T ib;                         /* '<Root>/ib' */
  real32_T ic;                         /* '<Root>/ic' */
  real32_T v_bus;                      /* '<Root>/v_bus' */
  real32_T Tpwm;                       /* '<Root>/Tpwm' */
  real32_T speedref;                   /* '<Root>/speedref' */
  real32_T ControlEnable;              /* '<Root>/ControlEnable' */
  real32_T Reset;                      /* '<Root>/Reset' */
  real32_T FaultActive;                /* '<Root>/FaultActive' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T switch_n;                   /* '<Root>/switch_n' */
  real32_T switch_theta;               /* '<Root>/switch_theta' */
  real_T Tcm1;                         /* '<Root>/Tcm1' */
  real_T Tcm2;                         /* '<Root>/Tcm2' */
  real_T Tcm3;                         /* '<Root>/Tcm3' */
  real32_T ModelState;                 /* '<Root>/ModelState' */
  real32_T ControlReady;               /* '<Root>/ControlReady' */
  boolean_T ObserverReady;             /* '<Root>/ObserverReady' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
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

/* Model entry point functions */
extern void FOC_Model_initialize(void);
extern void FOC_Model_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S8>/Data Type Propagation' : Unused code path elimination
 * Block '<S25>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S26>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S4>/Gain' : Unused code path elimination
 * Block '<S15>/Abs' : Unused code path elimination
 * Block '<S15>/Abs1' : Unused code path elimination
 * Block '<S15>/Add2' : Unused code path elimination
 * Block '<S15>/Add3' : Unused code path elimination
 * Block '<S15>/Add4' : Unused code path elimination
 * Block '<S15>/Add5' : Unused code path elimination
 * Block '<S15>/Add6' : Unused code path elimination
 * Block '<S15>/Add7' : Unused code path elimination
 * Block '<S15>/Add8' : Unused code path elimination
 * Block '<S15>/Constant' : Unused code path elimination
 * Block '<S15>/Constant1' : Unused code path elimination
 * Block '<S15>/Constant2' : Unused code path elimination
 * Block '<S15>/Constant3' : Unused code path elimination
 * Block '<S15>/Cos' : Unused code path elimination
 * Block '<S78>/Data Type Duplicate' : Unused code path elimination
 * Block '<S78>/Diff' : Unused code path elimination
 * Block '<S78>/TSamp' : Unused code path elimination
 * Block '<S78>/UD' : Unused code path elimination
 * Block '<S15>/Gain' : Unused code path elimination
 * Block '<S15>/Gain1' : Unused code path elimination
 * Block '<S15>/Gain10' : Unused code path elimination
 * Block '<S15>/Gain11' : Unused code path elimination
 * Block '<S15>/Gain12' : Unused code path elimination
 * Block '<S15>/Gain2' : Unused code path elimination
 * Block '<S15>/Product10' : Unused code path elimination
 * Block '<S15>/Product11' : Unused code path elimination
 * Block '<S15>/Product12' : Unused code path elimination
 * Block '<S15>/Product2' : Unused code path elimination
 * Block '<S15>/Product3' : Unused code path elimination
 * Block '<S15>/Product4' : Unused code path elimination
 * Block '<S15>/Product5' : Unused code path elimination
 * Block '<S15>/Product6' : Unused code path elimination
 * Block '<S15>/Product7' : Unused code path elimination
 * Block '<S15>/Product8' : Unused code path elimination
 * Block '<S15>/Product9' : Unused code path elimination
 * Block '<S15>/Scope' : Unused code path elimination
 * Block '<S15>/Scope1' : Unused code path elimination
 * Block '<S15>/Scope2' : Unused code path elimination
 * Block '<S15>/Scope3' : Unused code path elimination
 * Block '<S15>/Scope4' : Unused code path elimination
 * Block '<S15>/Sign' : Unused code path elimination
 * Block '<S15>/Sign1' : Unused code path elimination
 * Block '<S15>/Sin' : Unused code path elimination
 * Block '<S15>/Sum' : Unused code path elimination
 * Block '<S4>/Scope' : Unused code path elimination
 * Block '<S4>/Scope1' : Unused code path elimination
 * Block '<S4>/Scope10' : Unused code path elimination
 * Block '<S4>/Scope11' : Unused code path elimination
 * Block '<S4>/Scope12' : Unused code path elimination
 * Block '<S4>/Scope14' : Unused code path elimination
 * Block '<S4>/Scope15' : Unused code path elimination
 * Block '<S4>/Scope16' : Unused code path elimination
 * Block '<S4>/Scope17' : Unused code path elimination
 * Block '<S4>/Scope2' : Unused code path elimination
 * Block '<S4>/Scope25' : Unused code path elimination
 * Block '<S4>/Scope3' : Unused code path elimination
 * Block '<S4>/Scope4' : Unused code path elimination
 * Block '<S4>/Scope6' : Unused code path elimination
 * Block '<S4>/Scope7' : Unused code path elimination
 * Block '<S4>/Scope8' : Unused code path elimination
 * Block '<S4>/Scope9' : Unused code path elimination
 * Block '<S108>/DTDup' : Unused code path elimination
 * Block '<S21>/Scope' : Unused code path elimination
 * Block '<S22>/Gain' : Unused code path elimination
 * Block '<S22>/Gain1' : Unused code path elimination
 * Block '<S22>/Gain2' : Unused code path elimination
 * Block '<S22>/Product' : Unused code path elimination
 * Block '<S22>/Product1' : Unused code path elimination
 * Block '<S22>/Sum' : Unused code path elimination
 * Block '<S23>/Iabc2' : Unused code path elimination
 * Block '<S172>/DTDup' : Unused code path elimination
 * Block '<S5>/Scope2' : Unused code path elimination
 * Block '<S10>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S11>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S53>/Kb' : Eliminated nontunable gain of 1
 * Block '<S15>/Gain13' : Eliminated nontunable gain of 1
 * Block '<S15>/Gain14' : Eliminated nontunable gain of 1
 * Block '<S134>/Gain2' : Eliminated nontunable gain of 1
 * Block '<S169>/Kb' : Eliminated nontunable gain of 1
 * Block '<S184>/Proportional Gain' : Eliminated nontunable gain of 1
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
 * hilite_system('HFI_UB/FOC_Model')    - opens subsystem HFI_UB/FOC_Model
 * hilite_system('HFI_UB/FOC_Model/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'HFI_UB'
 * '<S1>'   : 'HFI_UB/FOC_Model'
 * '<S2>'   : 'HFI_UB/FOC_Model/ObserverModeIsSMO'
 * '<S3>'   : 'HFI_UB/FOC_Model/StartupManager'
 * '<S4>'   : 'HFI_UB/FOC_Model/currloop'
 * '<S5>'   : 'HFI_UB/FOC_Model/speedloop'
 * '<S6>'   : 'HFI_UB/FOC_Model/currloop/Anti_Park1'
 * '<S7>'   : 'HFI_UB/FOC_Model/currloop/CLARKE'
 * '<S8>'   : 'HFI_UB/FOC_Model/currloop/Counter Limited'
 * '<S9>'   : 'HFI_UB/FOC_Model/currloop/DirectionLatch'
 * '<S10>'  : 'HFI_UB/FOC_Model/currloop/Id1'
 * '<S11>'  : 'HFI_UB/FOC_Model/currloop/Iq'
 * '<S12>'  : 'HFI_UB/FOC_Model/currloop/MATLAB Function'
 * '<S13>'  : 'HFI_UB/FOC_Model/currloop/PARK'
 * '<S14>'  : 'HFI_UB/FOC_Model/currloop/PLL'
 * '<S15>'  : 'HFI_UB/FOC_Model/currloop/SMO1'
 * '<S16>'  : 'HFI_UB/FOC_Model/currloop/SVPWM MATLAB Function'
 * '<S17>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1'
 * '<S18>'  : 'HFI_UB/FOC_Model/currloop/Subsystem2'
 * '<S19>'  : 'HFI_UB/FOC_Model/currloop/Subsystem4'
 * '<S20>'  : 'HFI_UB/FOC_Model/currloop/Subsystem5'
 * '<S21>'  : 'HFI_UB/FOC_Model/currloop/polo'
 * '<S22>'  : 'HFI_UB/FOC_Model/currloop/前馈解耦'
 * '<S23>'  : 'HFI_UB/FOC_Model/currloop/死区补偿值计算'
 * '<S24>'  : 'HFI_UB/FOC_Model/currloop/求定子电流矢量角'
 * '<S25>'  : 'HFI_UB/FOC_Model/currloop/Counter Limited/Increment Real World'
 * '<S26>'  : 'HFI_UB/FOC_Model/currloop/Counter Limited/Wrap To Zero'
 * '<S27>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller'
 * '<S28>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Anti-windup'
 * '<S29>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/D Gain'
 * '<S30>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/External Derivative'
 * '<S31>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Filter'
 * '<S32>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Filter ICs'
 * '<S33>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/I Gain'
 * '<S34>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Ideal P Gain'
 * '<S35>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Ideal P Gain Fdbk'
 * '<S36>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Integrator'
 * '<S37>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Integrator ICs'
 * '<S38>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/N Copy'
 * '<S39>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/N Gain'
 * '<S40>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/P Copy'
 * '<S41>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Parallel P Gain'
 * '<S42>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Reset Signal'
 * '<S43>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Saturation'
 * '<S44>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Saturation Fdbk'
 * '<S45>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Sum'
 * '<S46>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Sum Fdbk'
 * '<S47>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Tracking Mode'
 * '<S48>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Tracking Mode Sum'
 * '<S49>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Tsamp - Integral'
 * '<S50>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Tsamp - Ngain'
 * '<S51>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/postSat Signal'
 * '<S52>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/preSat Signal'
 * '<S53>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Anti-windup/Back Calculation'
 * '<S54>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/D Gain/Internal Parameters'
 * '<S55>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/External Derivative/Error'
 * '<S56>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S57>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S58>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/I Gain/Internal Parameters'
 * '<S59>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Ideal P Gain/Passthrough'
 * '<S60>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S61>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Integrator/Discrete'
 * '<S62>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Integrator ICs/Internal IC'
 * '<S63>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/N Copy/Disabled'
 * '<S64>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/N Gain/Internal Parameters'
 * '<S65>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/P Copy/Disabled'
 * '<S66>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S67>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Reset Signal/Disabled'
 * '<S68>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Saturation/Enabled'
 * '<S69>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Saturation Fdbk/Disabled'
 * '<S70>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Sum/Sum_PID'
 * '<S71>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Sum Fdbk/Disabled'
 * '<S72>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Tracking Mode/Disabled'
 * '<S73>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S74>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S75>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S76>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/postSat Signal/Forward_Path'
 * '<S77>'  : 'HFI_UB/FOC_Model/currloop/PLL/PID Controller/preSat Signal/Forward_Path'
 * '<S78>'  : 'HFI_UB/FOC_Model/currloop/SMO1/Discrete Derivative'
 * '<S79>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1'
 * '<S80>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Anti-windup'
 * '<S81>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/D Gain'
 * '<S82>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/External Derivative'
 * '<S83>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Filter'
 * '<S84>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Filter ICs'
 * '<S85>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/I Gain'
 * '<S86>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Ideal P Gain'
 * '<S87>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Ideal P Gain Fdbk'
 * '<S88>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Integrator'
 * '<S89>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Integrator ICs'
 * '<S90>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/N Copy'
 * '<S91>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/N Gain'
 * '<S92>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/P Copy'
 * '<S93>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Parallel P Gain'
 * '<S94>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Reset Signal'
 * '<S95>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Saturation'
 * '<S96>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Saturation Fdbk'
 * '<S97>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Sum'
 * '<S98>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Sum Fdbk'
 * '<S99>'  : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Tracking Mode'
 * '<S100>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Tracking Mode Sum'
 * '<S101>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Tsamp - Integral'
 * '<S102>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Tsamp - Ngain'
 * '<S103>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/postSat Signal'
 * '<S104>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/preSat Signal'
 * '<S105>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Anti-windup/Passthrough'
 * '<S106>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/D Gain/Internal Parameters'
 * '<S107>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/External Derivative/Error'
 * '<S108>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Filter/Differentiator'
 * '<S109>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Filter/Differentiator/Tsamp'
 * '<S110>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Filter/Differentiator/Tsamp/Internal Ts'
 * '<S111>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Filter ICs/Internal IC - Differentiator'
 * '<S112>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/I Gain/Internal Parameters'
 * '<S113>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Ideal P Gain/Passthrough'
 * '<S114>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S115>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Integrator/Discrete'
 * '<S116>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Integrator ICs/Internal IC'
 * '<S117>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S118>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/N Gain/Passthrough'
 * '<S119>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/P Copy/Disabled'
 * '<S120>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S121>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Reset Signal/Disabled'
 * '<S122>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Saturation/Passthrough'
 * '<S123>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Saturation Fdbk/Disabled'
 * '<S124>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Sum/Sum_PID'
 * '<S125>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Sum Fdbk/Disabled'
 * '<S126>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Tracking Mode/Disabled'
 * '<S127>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S128>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S129>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S130>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/postSat Signal/Forward_Path'
 * '<S131>' : 'HFI_UB/FOC_Model/currloop/Subsystem1/Discrete PID Controller1/preSat Signal/Forward_Path'
 * '<S132>' : 'HFI_UB/FOC_Model/currloop/polo/PolarityLatch'
 * '<S133>' : 'HFI_UB/FOC_Model/currloop/求定子电流矢量角/Id ~=0'
 * '<S134>' : 'HFI_UB/FOC_Model/currloop/求定子电流矢量角/Id= =0'
 * '<S135>' : 'HFI_UB/FOC_Model/currloop/求定子电流矢量角/If Action Subsystem'
 * '<S136>' : 'HFI_UB/FOC_Model/currloop/求定子电流矢量角/If Action Subsystem1'
 * '<S137>' : 'HFI_UB/FOC_Model/currloop/求定子电流矢量角/Id ~=0/If Action Subsystem'
 * '<S138>' : 'HFI_UB/FOC_Model/currloop/求定子电流矢量角/Id ~=0/If Action Subsystem1'
 * '<S139>' : 'HFI_UB/FOC_Model/currloop/求定子电流矢量角/Id ~=0/id1<=0'
 * '<S140>' : 'HFI_UB/FOC_Model/currloop/求定子电流矢量角/Id ~=0/id1>0'
 * '<S141>' : 'HFI_UB/FOC_Model/currloop/求定子电流矢量角/Id ~=0/id<=0'
 * '<S142>' : 'HFI_UB/FOC_Model/currloop/求定子电流矢量角/Id ~=0/id>0'
 * '<S143>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller'
 * '<S144>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Anti-windup'
 * '<S145>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/D Gain'
 * '<S146>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/External Derivative'
 * '<S147>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Filter'
 * '<S148>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Filter ICs'
 * '<S149>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/I Gain'
 * '<S150>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Ideal P Gain'
 * '<S151>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S152>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Integrator'
 * '<S153>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Integrator ICs'
 * '<S154>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/N Copy'
 * '<S155>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/N Gain'
 * '<S156>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/P Copy'
 * '<S157>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Parallel P Gain'
 * '<S158>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Reset Signal'
 * '<S159>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Saturation'
 * '<S160>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Saturation Fdbk'
 * '<S161>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Sum'
 * '<S162>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Sum Fdbk'
 * '<S163>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Tracking Mode'
 * '<S164>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Tracking Mode Sum'
 * '<S165>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Tsamp - Integral'
 * '<S166>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Tsamp - Ngain'
 * '<S167>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/postSat Signal'
 * '<S168>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/preSat Signal'
 * '<S169>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Anti-windup/Back Calculation'
 * '<S170>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/D Gain/Internal Parameters'
 * '<S171>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/External Derivative/Error'
 * '<S172>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Filter/Differentiator'
 * '<S173>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Filter/Differentiator/Tsamp'
 * '<S174>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Filter/Differentiator/Tsamp/Internal Ts'
 * '<S175>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Filter ICs/Internal IC - Differentiator'
 * '<S176>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S177>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S178>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S179>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Integrator/Discrete'
 * '<S180>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S181>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/N Copy/Disabled wSignal Specification'
 * '<S182>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/N Gain/Passthrough'
 * '<S183>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/P Copy/Disabled'
 * '<S184>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S185>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Reset Signal/Disabled'
 * '<S186>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Saturation/Enabled'
 * '<S187>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S188>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Sum/Sum_PID'
 * '<S189>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S190>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S191>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S192>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S193>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S194>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S195>' : 'HFI_UB/FOC_Model/speedloop/Discrete PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* FOC_Model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
