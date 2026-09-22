/*
 * File: FOC_Model.c
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

#include "FOC_Model.h"
#include "rtwtypes.h"
#include <math.h>
#include <stddef.h>
#include <float.h>

/* Named constants for Chart: '<S2>/Chart1' */
#define IN_AlignStage                  ((uint8_T)1U)
#define IN_IDLE                        ((uint8_T)2U)
#define IN_OpenStage                   ((uint8_T)3U)
#define IN_RunStage                    ((uint8_T)4U)
#define NumBitsPerChar                 8U

/* Exported block signals */
real32_T SMO_Theta;                    /* '<S19>/Unit Delay' */
real32_T SMO_Wm;                       /* '<S12>/Gain1' */
real32_T Motor_state;                  /* '<S2>/Chart1' */
real32_T SpeedFd;                      /* '<S179>/Gain' */

/* Exported data definition */

/* Definition for custom storage class: Struct */
CurrKPKI_type CurrKPKI = {
  /* CurrKi */
  2.3F,

  /* CurrKp */
  0.0008F
};

ObGain_type ObGain = {
  /* GainK */
  -100.0F,

  /* GainM */
  3000.0F
};

motor_type motor = {
  /* L */
  8.0E-5F,

  /* Pn */
  4.0F,

  /* Rs */
  0.23F
};

spd_kpki_type spd_kpki = {
  /* spd_ki */
  0.021F,

  /* spd_kp */
  0.013F
};

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern real32_T rt_modf_snf(real32_T u0, real32_T u1);
static void SVPWM(real32_T rtu_Valpha, real32_T rtu_Vbeta, real32_T rtu_v_bus,
                  real32_T rty_tABC[3]);
static void rate_scheduler(void);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);

#define NOT_USING_NONFINITE_LITERALS   1

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (rtM->Timing.TaskCounters.TID[1])++;
  if ((rtM->Timing.TaskCounters.TID[1]) > 9) {/* Sample time: [0.001s, 0.0s] */
    rtM->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Output and update for atomic system: '<S2>/SVPWM' */
static void SVPWM(real32_T rtu_Valpha, real32_T rtu_Vbeta, real32_T rtu_v_bus,
                  real32_T rty_tABC[3])
{
  real32_T rtb_Min;
  real32_T rtb_Sum1_a;
  real32_T rtb_Sum_o;

  /* Gain: '<S74>/Gain' */
  rtb_Min = -0.5F * rtu_Valpha;

  /* Gain: '<S74>/Gain1' */
  rtb_Sum1_a = 0.866025388F * rtu_Vbeta;

  /* Sum: '<S74>/Sum' */
  rtb_Sum_o = rtb_Min + rtb_Sum1_a;

  /* Sum: '<S74>/Sum1' */
  rtb_Sum1_a = rtb_Min - rtb_Sum1_a;

  /* Gain: '<S75>/Gain' incorporates:
   *  MinMax: '<S75>/Min'
   *  MinMax: '<S75>/Min1'
   *  Sum: '<S75>/Sum'
   */
  rtb_Min = (fminf(fminf(rtu_Valpha, rtb_Sum_o), rtb_Sum1_a) + fmaxf(fmaxf
              (rtu_Valpha, rtb_Sum_o), rtb_Sum1_a)) * -0.5F;

  /* Sum: '<S13>/Sum' */
  rty_tABC[0] = rtb_Min + rtu_Valpha;
  rty_tABC[1] = rtb_Min + rtb_Sum_o;
  rty_tABC[2] = rtb_Min + rtb_Sum1_a;

  /* Gain: '<S13>/PWM_HalfPeriod' incorporates:
   *  Constant: '<S13>/Constant'
   *  Gain: '<S13>/Gain'
   *  Product: '<S13>/Divide'
   *  Sum: '<S13>/Sum1'
   */
  rty_tABC[0] = (-rty_tABC[0] / rtu_v_bus + 0.5F) * 8000.0F;
  rty_tABC[1] = (-rty_tABC[1] / rtu_v_bus + 0.5F) * 8000.0F;
  rty_tABC[2] = (-rty_tABC[2] / rtu_v_bus + 0.5F) * 8000.0F;
}

real32_T rt_modf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  y = u0;
  if (u1 == 0.0F) {
    if (u0 == 0.0F) {
      y = u1;
    }
  } else if (rtIsNaNF(u0) || rtIsNaNF(u1) || rtIsInfF(u0)) {
    y = (rtNaNF);
  } else if (u0 == 0.0F) {
    y = 0.0F / u1;
  } else if (rtIsInfF(u1)) {
    if ((u1 < 0.0F) != (u0 < 0.0F)) {
      y = u1;
    }
  } else {
    boolean_T yEq;
    y = fmodf(u0, u1);
    yEq = (y == 0.0F);
    if ((!yEq) && (u1 > floorf(u1))) {
      real32_T q;
      q = fabsf(u0 / u1);
      yEq = !(fabsf(q - floorf(q + 0.5F)) > FLT_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0F;
    } else if ((u0 < 0.0F) != (u1 < 0.0F)) {
      y += u1;
    }
  }

  return y;
}

/* Model step function */
void FOC_Model_step(void)
{
  real32_T Integrator;
  real32_T rtb_Add1_h;
  real32_T rtb_Add_o;
  real32_T rtb_DeadZone_e;
  real32_T rtb_DeadZone_n;
  real32_T rtb_IntegralGain;
  real32_T rtb_IntegralGain_h;
  real32_T rtb_Integrator_nt;
  real32_T rtb_Merge1_h;
  real32_T rtb_Saturation;
  real32_T rtb_Sign;
  real32_T rtb_Sign1;
  real32_T rtb_Sign_tmp;
  real32_T rtb_UnitDelay2;
  real32_T rtb_UnitDelay3;
  uint32_T speedloop_ELAPS_T;
  int8_T tmp;
  int8_T tmp_0;
  boolean_T rtb_AND3_j;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_Model' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
     *  SubSystem: '<S1>/speedloop'
     */
    if (rtDW.speedloop_RESET_ELAPS_T) {
      speedloop_ELAPS_T = 0U;
    } else {
      speedloop_ELAPS_T = rtM->Timing.clockTick1 - rtDW.speedloop_PREV_T;
    }

    rtDW.speedloop_PREV_T = rtM->Timing.clockTick1;
    rtDW.speedloop_RESET_ELAPS_T = false;

    /* Sum: '<S3>/Sum2' incorporates:
     *  Inport: '<Root>/SpeedRef'
     *  UnitDelay: '<S1>/Unit Delay1'
     */
    rtb_IntegralGain = rtU.SpeedRef - SMO_Wm;

    /* DiscreteIntegrator: '<S213>/Integrator' incorporates:
     *  UnitDelay: '<S1>/Unit Delay'
     */
    if (rtDW.Integrator_SYSTEM_ENABLE != 0) {
      /* DiscreteIntegrator: '<S213>/Integrator' */
      Integrator = rtDW.Integrator_DSTATE_h;
    } else if ((rtDW.SpeedReset > 0.0) && (rtDW.Integrator_PrevResetState <= 0))
    {
      /* DiscreteIntegrator: '<S213>/Integrator' */
      Integrator = 0.0F;
    } else {
      /* DiscreteIntegrator: '<S213>/Integrator' */
      Integrator = (real32_T)(0.001 * (real_T)speedloop_ELAPS_T
        * rtDW.Integrator_PREV_U) + rtDW.Integrator_DSTATE_h;
    }

    /* End of DiscreteIntegrator: '<S213>/Integrator' */

    /* Sum: '<S222>/Sum' incorporates:
     *  Gain: '<S218>/Proportional Gain'
     */
    rtb_Merge1_h = spd_kpki.spd_kp * rtb_IntegralGain + Integrator;

    /* Saturate: '<S220>/Saturation' incorporates:
     *  DeadZone: '<S206>/DeadZone'
     */
    if (rtb_Merge1_h > 20.0F) {
      /* Saturate: '<S220>/Saturation' */
      rtDW.Saturation = 20.0F;
      rtb_Merge1_h -= 20.0F;
    } else {
      if (rtb_Merge1_h < -20.0F) {
        /* Saturate: '<S220>/Saturation' */
        rtDW.Saturation = -20.0F;
      } else {
        /* Saturate: '<S220>/Saturation' */
        rtDW.Saturation = rtb_Merge1_h;
      }

      if (rtb_Merge1_h >= -20.0F) {
        rtb_Merge1_h = 0.0F;
      } else {
        rtb_Merge1_h -= -20.0F;
      }
    }

    /* End of Saturate: '<S220>/Saturation' */

    /* Gain: '<S210>/Integral Gain' */
    rtb_IntegralGain *= spd_kpki.spd_ki;

    /* Switch: '<S204>/Switch1' incorporates:
     *  Constant: '<S204>/Clamping_zero'
     *  Constant: '<S204>/Constant'
     *  Constant: '<S204>/Constant2'
     *  RelationalOperator: '<S204>/fix for DT propagation issue'
     */
    if (rtb_Merge1_h > 0.0F) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S204>/Switch2' incorporates:
     *  Constant: '<S204>/Clamping_zero'
     *  Constant: '<S204>/Constant3'
     *  Constant: '<S204>/Constant4'
     *  RelationalOperator: '<S204>/fix for DT propagation issue1'
     */
    if (rtb_IntegralGain > 0.0F) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Logic: '<S204>/AND3' incorporates:
     *  Constant: '<S204>/Clamping_zero'
     *  RelationalOperator: '<S204>/Equal1'
     *  RelationalOperator: '<S204>/Relational Operator'
     *  Switch: '<S204>/Switch1'
     *  Switch: '<S204>/Switch2'
     */
    rtb_AND3_j = ((rtb_Merge1_h != 0.0F) && (tmp == tmp_0));

    /* Sum: '<S179>/Sum1' incorporates:
     *  Inport: '<Root>/Encoder_Theta'
     *  UnitDelay: '<S179>/Unit Delay'
     */
    rtb_Merge1_h = rtU.Encoder_Theta - rtDW.UnitDelay_DSTATE_g;

    /* If: '<S230>/If1' incorporates:
     *  Constant: '<S232>/2pi'
     *  Constant: '<S233>/2pi'
     *  Gain: '<S179>/Gain'
     *  Gain: '<S179>/Gain1'
     *  Gain: '<S231>/Gain'
     *  Gain: '<S232>/Gain'
     *  Gain: '<S233>/Gain'
     *  Sum: '<S232>/Subtract1'
     *  Sum: '<S233>/Subtract1'
     */
    if (rtb_Merge1_h > 4.2F) {
      /* Outputs for IfAction SubSystem: '<S230>/If Action Subsystem2' incorporates:
       *  ActionPort: '<S232>/Action Port'
       */
      rtb_Merge1_h = (rtb_Merge1_h - 6.28318501F) * 1000.0F;

      /* End of Outputs for SubSystem: '<S230>/If Action Subsystem2' */
    } else if (rtb_Merge1_h < -4.2F) {
      /* Outputs for IfAction SubSystem: '<S230>/If Action Subsystem3' incorporates:
       *  ActionPort: '<S233>/Action Port'
       */
      rtb_Merge1_h = (rtb_Merge1_h + 6.28318501F) * 1000.0F;

      /* End of Outputs for SubSystem: '<S230>/If Action Subsystem3' */
    } else {
      /* Outputs for IfAction SubSystem: '<S230>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S231>/Action Port'
       */
      rtb_Merge1_h *= 1000.0F;

      /* End of Outputs for SubSystem: '<S230>/If Action Subsystem1' */
    }

    SpeedFd = 1.0F / motor.Pn * (9.54929638F * rtb_Merge1_h);

    /* End of If: '<S230>/If1' */

    /* Update for DiscreteIntegrator: '<S213>/Integrator' incorporates:
     *  UnitDelay: '<S1>/Unit Delay'
     */
    rtDW.Integrator_SYSTEM_ENABLE = 0U;
    rtDW.Integrator_DSTATE_h = Integrator;
    if (rtDW.SpeedReset > 0.0) {
      rtDW.Integrator_PrevResetState = 1;
    } else if (rtDW.SpeedReset < 0.0) {
      rtDW.Integrator_PrevResetState = -1;
    } else if (rtDW.SpeedReset == 0.0) {
      rtDW.Integrator_PrevResetState = 0;
    } else {
      rtDW.Integrator_PrevResetState = 2;
    }

    /* Switch: '<S204>/Switch' */
    if (rtb_AND3_j) {
      /* Update for DiscreteIntegrator: '<S213>/Integrator' incorporates:
       *  Constant: '<S204>/Constant1'
       */
      rtDW.Integrator_PREV_U = 0.0F;
    } else {
      /* Update for DiscreteIntegrator: '<S213>/Integrator' */
      rtDW.Integrator_PREV_U = rtb_IntegralGain;
    }

    /* End of Switch: '<S204>/Switch' */

    /* Update for UnitDelay: '<S179>/Unit Delay' incorporates:
     *  Inport: '<Root>/Encoder_Theta'
     */
    rtDW.UnitDelay_DSTATE_g = rtU.Encoder_Theta;

    /* End of Outputs for S-Function (fcgen): '<S1>/Function-Call Generator' */
  }

  /* Outputs for Atomic SubSystem: '<S1>/currloop' */
  /* Chart: '<S2>/Chart1' incorporates:
   *  Inport: '<Root>/Motor_OnOff'
   */
  if (rtDW.temporalCounter_i1 < 32767U) {
    rtDW.temporalCounter_i1++;
  }

  if (rtDW.is_active_c1_FOC_Model == 0U) {
    rtDW.is_active_c1_FOC_Model = 1U;
    rtDW.is_c1_FOC_Model = IN_IDLE;
  } else {
    switch (rtDW.is_c1_FOC_Model) {
     case IN_AlignStage:
      if (rtDW.temporalCounter_i1 >= 1000) {
        rtDW.temporalCounter_i1 = 0U;
        rtDW.is_c1_FOC_Model = IN_OpenStage;
        rtDW.ZReset = 0.0;
      } else if (rtU.Motor_OnOff == 0.0F) {
        rtDW.is_c1_FOC_Model = IN_IDLE;
      } else {
        Motor_state = 2.0F;
      }
      break;

     case IN_IDLE:
      if (rtU.Motor_OnOff == 1.0F) {
        rtDW.temporalCounter_i1 = 0U;
        rtDW.is_c1_FOC_Model = IN_AlignStage;
        rtDW.ZReset = 0.0;
        rtDW.SpeedReset = 0.0;
      } else {
        Motor_state = 1.0F;
      }
      break;

     case IN_OpenStage:
      if (rtU.Motor_OnOff == 0.0F) {
        rtDW.is_c1_FOC_Model = IN_IDLE;
      } else if (rtDW.temporalCounter_i1 >= 30000) {
        rtDW.is_c1_FOC_Model = IN_RunStage;
      } else {
        rtDW.ZReset = 1.0;
        Motor_state = 3.0F;
      }
      break;

     default:
      /* case IN_RunStage: */
      if (rtU.Motor_OnOff == 0.0F) {
        rtDW.is_c1_FOC_Model = IN_IDLE;
      } else {
        Motor_state = 4.0F;
        rtDW.SpeedReset = 1.0;
      }
      break;
    }
  }

  /* End of Chart: '<S2>/Chart1' */

  /* UnitDelay: '<S19>/Unit Delay' */
  SMO_Theta = rtDW.UnitDelay_DSTATE_m;

  /* SwitchCase: '<S2>/Switch Case1' */
  switch ((int32_T)Motor_state) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    /* Merge: '<S2>/Merge3' incorporates:
     *  Constant: '<S7>/Constant'
     *  SignalConversion generated from: '<S7>/theta_fd'
     */
    rtDW.Merge3 = 0.0F;

    /* Merge: '<S2>/Merge4' incorporates:
     *  Constant: '<S7>/Constant1'
     *  SignalConversion generated from: '<S7>/iq_ref'
     */
    rtDW.Merge4 = 0.0F;

    /* Merge: '<S2>/Merge5' incorporates:
     *  Constant: '<S7>/Constant2'
     *  SignalConversion generated from: '<S7>/id_ref'
     */
    rtDW.Merge5 = 0.0F;

    /* End of Outputs for SubSystem: '<S2>/If Action Subsystem3' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem4' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
    /* Merge: '<S2>/Merge3' incorporates:
     *  Constant: '<S8>/Constant'
     *  SignalConversion generated from: '<S8>/theta_fd'
     */
    rtDW.Merge3 = 0.0F;

    /* Merge: '<S2>/Merge4' incorporates:
     *  Constant: '<S8>/Constant1'
     *  SignalConversion generated from: '<S8>/iq_ref'
     */
    rtDW.Merge4 = 0.0F;

    /* Merge: '<S2>/Merge5' incorporates:
     *  Constant: '<S8>/Constant2'
     *  SignalConversion generated from: '<S8>/id_ref'
     */
    rtDW.Merge5 = 2.0F;

    /* End of Outputs for SubSystem: '<S2>/If Action Subsystem4' */
    break;

   case 3:
    /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem5' incorporates:
     *  ActionPort: '<S9>/Action Port'
     */
    /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator' */
    if ((rtDW.ZReset > 0.0) && (rtDW.DiscreteTimeIntegrator_PrevRese <= 0)) {
      rtDW.DiscreteTimeIntegrator_DSTATE = 0.0F;
    }

    rtb_IntegralGain = rtDW.DiscreteTimeIntegrator_DSTATE;

    /* End of DiscreteIntegrator: '<S9>/Discrete-Time Integrator' */

    /* DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
    if ((rtDW.ZReset > 0.0) && (rtDW.DiscreteTimeIntegrator1_PrevRes <= 0)) {
      rtDW.DiscreteTimeIntegrator1_DSTATE = 0.0F;
    }

    /* Merge: '<S2>/Merge3' incorporates:
     *  Constant: '<S9>/Constant1'
     *  DiscreteIntegrator: '<S9>/Discrete-Time Integrator1'
     *  Math: '<S9>/Mod'
     */
    rtDW.Merge3 = rt_modf_snf(rtDW.DiscreteTimeIntegrator1_DSTATE, 6.28318501F);

    /* Merge: '<S2>/Merge4' incorporates:
     *  Constant: '<S9>/Constant3'
     *  SignalConversion generated from: '<S9>/iq_ref'
     */
    rtDW.Merge4 = 0.0F;

    /* Merge: '<S2>/Merge5' incorporates:
     *  Constant: '<S9>/Constant5'
     *  SignalConversion generated from: '<S9>/id_ref'
     */
    rtDW.Merge5 = 2.0F;

    /* Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator' incorporates:
     *  Gain: '<S9>/Gain'
     *  Product: '<S9>/Product'
     */
    rtDW.DiscreteTimeIntegrator_DSTATE += motor.Pn * 83.7758F * 0.333333343F *
      0.0001F;
    if (rtDW.ZReset > 0.0) {
      rtDW.DiscreteTimeIntegrator_PrevRese = 1;
    } else if (rtDW.ZReset < 0.0) {
      rtDW.DiscreteTimeIntegrator_PrevRese = -1;
    } else if (rtDW.ZReset == 0.0) {
      rtDW.DiscreteTimeIntegrator_PrevRese = 0;
    } else {
      rtDW.DiscreteTimeIntegrator_PrevRese = 2;
    }

    /* End of Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator' */

    /* Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
    rtDW.DiscreteTimeIntegrator1_DSTATE += 0.0001F * rtb_IntegralGain;
    if (rtDW.ZReset > 0.0) {
      rtDW.DiscreteTimeIntegrator1_PrevRes = 1;
    } else if (rtDW.ZReset < 0.0) {
      rtDW.DiscreteTimeIntegrator1_PrevRes = -1;
    } else if (rtDW.ZReset == 0.0) {
      rtDW.DiscreteTimeIntegrator1_PrevRes = 0;
    } else {
      rtDW.DiscreteTimeIntegrator1_PrevRes = 2;
    }

    /* End of Update for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
    /* End of Outputs for SubSystem: '<S2>/If Action Subsystem5' */
    break;

   case 4:
    /* Outputs for IfAction SubSystem: '<S2>/If Action Subsystem6' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    /* Merge: '<S2>/Merge5' incorporates:
     *  Constant: '<S10>/Constant5'
     *  SignalConversion generated from: '<S10>/id_ref'
     */
    rtDW.Merge5 = 0.0F;

    /* Merge: '<S2>/Merge3' incorporates:
     *  SignalConversion generated from: '<S10>/Theta'
     */
    rtDW.Merge3 = SMO_Theta;

    /* Merge: '<S2>/Merge4' incorporates:
     *  SignalConversion generated from: '<S10>/Iq_Ref'
     */
    rtDW.Merge4 = rtDW.Saturation;

    /* End of Outputs for SubSystem: '<S2>/If Action Subsystem6' */
    break;
  }

  /* End of SwitchCase: '<S2>/Switch Case1' */

  /* Sum: '<S6>/Add1' incorporates:
   *  Gain: '<S6>/Gain'
   *  Gain: '<S6>/Gain1'
   *  Inport: '<Root>/ia'
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   *  Sum: '<S6>/Add'
   */
  rtb_Sign = 0.666666687F * rtU.ia - (rtU.ib + rtU.ic) * 0.333333343F;

  /* Trigonometry: '<S2>/SinCos1' */
  rtb_Integrator_nt = cosf(rtDW.Merge3);

  /* Gain: '<S6>/Gain2' incorporates:
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   *  Sum: '<S6>/Add2'
   */
  rtb_Sign1 = (rtU.ib - rtU.ic) * 0.577350259F;

  /* Trigonometry: '<S2>/SinCos' */
  rtb_UnitDelay3 = sinf(rtDW.Merge3);

  /* Sum: '<S14>/Sum1' incorporates:
   *  Product: '<S11>/Product'
   *  Product: '<S11>/Product1'
   *  Sum: '<S11>/Add'
   */
  rtb_IntegralGain = rtDW.Merge5 - (rtb_Sign * rtb_Integrator_nt + rtb_Sign1 *
    rtb_UnitDelay3);

  /* Sum: '<S120>/Sum' incorporates:
   *  Constant: '<S14>/Constant3'
   *  DiscreteIntegrator: '<S111>/Integrator'
   *  Product: '<S116>/PProd Out'
   */
  Integrator = rtb_IntegralGain * CurrKPKI.CurrKp + rtDW.Integrator_DSTATE;

  /* Saturate: '<S118>/Saturation' */
  if (Integrator > 12.4707661F) {
    rtb_UnitDelay2 = 12.4707661F;
  } else if (Integrator < -12.4707661F) {
    rtb_UnitDelay2 = -12.4707661F;
  } else {
    rtb_UnitDelay2 = Integrator;
  }

  /* End of Saturate: '<S118>/Saturation' */

  /* Sum: '<S14>/Sum7' incorporates:
   *  Product: '<S11>/Product2'
   *  Product: '<S11>/Product3'
   *  Sum: '<S11>/Add1'
   */
  rtb_Merge1_h = rtDW.Merge4 - (rtb_Sign1 * rtb_Integrator_nt - rtb_Sign *
    rtb_UnitDelay3);

  /* Sum: '<S170>/Sum' incorporates:
   *  Constant: '<S14>/Constant1'
   *  DiscreteIntegrator: '<S161>/Integrator'
   *  Product: '<S166>/PProd Out'
   */
  rtb_DeadZone_e = rtb_Merge1_h * CurrKPKI.CurrKp + rtDW.Integrator_DSTATE_b;

  /* Saturate: '<S168>/Saturation' */
  if (rtb_DeadZone_e > 12.4707661F) {
    rtb_IntegralGain_h = 12.4707661F;
  } else if (rtb_DeadZone_e < -12.4707661F) {
    rtb_IntegralGain_h = -12.4707661F;
  } else {
    rtb_IntegralGain_h = rtb_DeadZone_e;
  }

  /* End of Saturate: '<S168>/Saturation' */

  /* Sum: '<S4>/Add' incorporates:
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product1'
   */
  rtb_Add_o = rtb_UnitDelay2 * rtb_Integrator_nt - rtb_IntegralGain_h *
    rtb_UnitDelay3;

  /* Sum: '<S4>/Add1' incorporates:
   *  Product: '<S4>/Product2'
   *  Product: '<S4>/Product3'
   */
  rtb_Integrator_nt = rtb_UnitDelay2 * rtb_UnitDelay3 + rtb_IntegralGain_h *
    rtb_Integrator_nt;

  /* Sum: '<S17>/Add8' incorporates:
   *  UnitDelay: '<S17>/Unit Delay4'
   */
  rtb_UnitDelay2 = rtDW.UnitDelay4_DSTATE - rtb_Sign;

  /* Signum: '<S17>/Sign' */
  if (rtIsNaNF(rtb_UnitDelay2)) {
    rtb_Sign = (rtNaNF);
  } else if (rtb_UnitDelay2 < 0.0F) {
    rtb_Sign = -1.0F;
  } else {
    rtb_Sign = (real32_T)(rtb_UnitDelay2 > 0.0F);
  }

  /* End of Signum: '<S17>/Sign' */

  /* Sum: '<S17>/Add11' incorporates:
   *  Delay: '<S12>/Delay'
   *  Gain: '<S17>/Gain20'
   *  Gain: '<S17>/Gain22'
   *  Product: '<S17>/Product2'
   *  UnitDelay: '<S17>/Unit Delay2'
   *  UnitDelay: '<S17>/Unit Delay3'
   */
  rtb_UnitDelay3 = (rtDW.UnitDelay2_DSTATE - 0.0001F * rtDW.Delay_DSTATE *
                    rtDW.UnitDelay3_DSTATE) + ObGain.GainM * 0.0001F * rtb_Sign;

  /* Sum: '<S17>/Add10' incorporates:
   *  UnitDelay: '<S17>/Unit Delay5'
   */
  rtb_UnitDelay2 = rtDW.UnitDelay5_DSTATE - rtb_Sign1;

  /* Signum: '<S17>/Sign1' */
  if (rtIsNaNF(rtb_UnitDelay2)) {
    rtb_Sign1 = (rtNaNF);
  } else if (rtb_UnitDelay2 < 0.0F) {
    rtb_Sign1 = -1.0F;
  } else {
    rtb_Sign1 = (real32_T)(rtb_UnitDelay2 > 0.0F);
  }

  /* End of Signum: '<S17>/Sign1' */

  /* Sum: '<S17>/Add12' incorporates:
   *  Delay: '<S12>/Delay'
   *  Gain: '<S17>/Gain24'
   *  Gain: '<S17>/Gain25'
   *  Product: '<S17>/Product3'
   *  UnitDelay: '<S17>/Unit Delay2'
   *  UnitDelay: '<S17>/Unit Delay3'
   */
  rtb_UnitDelay2 = (0.0001F * rtDW.Delay_DSTATE * rtDW.UnitDelay2_DSTATE +
                    rtDW.UnitDelay3_DSTATE) + ObGain.GainM * 0.0001F * rtb_Sign1;

  /* Sum: '<S16>/Add8' incorporates:
   *  Product: '<S16>/Product4'
   *  Product: '<S16>/Product5'
   *  Trigonometry: '<S16>/Cos'
   *  Trigonometry: '<S16>/Sin'
   */
  rtb_IntegralGain_h = (0.0F - rtb_UnitDelay3 * cosf(SMO_Theta)) -
    rtb_UnitDelay2 * sinf(SMO_Theta);

  /* Sum: '<S62>/Sum' incorporates:
   *  DiscreteIntegrator: '<S53>/Integrator'
   *  Gain: '<S58>/Proportional Gain'
   */
  rtb_DeadZone_n = 141.4F * rtb_IntegralGain_h + rtDW.Integrator_DSTATE_o;

  /* Saturate: '<S60>/Saturation' incorporates:
   *  DeadZone: '<S46>/DeadZone'
   */
  if (rtb_DeadZone_n > 2000.0F) {
    rtb_Saturation = 2000.0F;
    rtb_DeadZone_n -= 2000.0F;
  } else {
    if (rtb_DeadZone_n < -2000.0F) {
      rtb_Saturation = -2000.0F;
    } else {
      rtb_Saturation = rtb_DeadZone_n;
    }

    if (rtb_DeadZone_n >= -2000.0F) {
      rtb_DeadZone_n = 0.0F;
    } else {
      rtb_DeadZone_n -= -2000.0F;
    }
  }

  /* End of Saturate: '<S60>/Saturation' */

  /* Sum: '<S15>/Add1' incorporates:
   *  Constant: '<S15>/Constant'
   *  Delay: '<S15>/Delay'
   *  Product: '<S15>/Product'
   *  Sum: '<S15>/Add'
   */
  rtb_Add1_h = (rtb_Saturation - rtDW.Delay_DSTATE_j) * 0.03F +
    rtDW.Delay_DSTATE_j;

  /* Gain: '<S12>/Gain1' incorporates:
   *  Gain: '<S12>/Gain'
   */
  SMO_Wm = 1.0F / motor.Pn * rtb_Add1_h * 9.54929638F;

  /* Gain: '<S50>/Integral Gain' */
  rtb_IntegralGain_h *= 22500.0F;

  /* Sum: '<S19>/Sum1' incorporates:
   *  Gain: '<S19>/Ts'
   */
  rtb_Saturation = 0.0001F * rtb_Saturation + SMO_Theta;

  /* Gain: '<S17>/Gain' incorporates:
   *  Gain: '<S17>/Gain17'
   */
  rtb_Sign_tmp = 1.0F - motor.Rs * 0.0001F / motor.L;

  /* Sum: '<S17>/Add5' incorporates:
   *  Gain: '<S17>/Gain'
   *  Gain: '<S17>/Gain15'
   *  Gain: '<S17>/Gain16'
   *  Gain: '<S17>/Gain21'
   *  UnitDelay: '<S17>/Unit Delay'
   *  UnitDelay: '<S17>/Unit Delay2'
   */
  rtb_Sign = ((rtb_Sign_tmp * rtDW.UnitDelay_DSTATE_e - 0.0001F / motor.L *
               rtDW.UnitDelay2_DSTATE) + 0.0001F / motor.L * rtb_Add_o) +
    ObGain.GainK * 0.0001F * rtb_Sign;

  /* Sum: '<S17>/Add9' incorporates:
   *  Gain: '<S17>/Gain17'
   *  Gain: '<S17>/Gain18'
   *  Gain: '<S17>/Gain19'
   *  Gain: '<S17>/Gain23'
   *  UnitDelay: '<S17>/Unit Delay1'
   *  UnitDelay: '<S17>/Unit Delay3'
   */
  rtb_Sign1 = ((rtb_Sign_tmp * rtDW.UnitDelay1_DSTATE_j - 0.0001F / motor.L *
                rtDW.UnitDelay3_DSTATE) + 0.0001F / motor.L * rtb_Integrator_nt)
    + ObGain.GainK * 0.0001F * rtb_Sign1;

  /* Outputs for Atomic SubSystem: '<S2>/SVPWM' */
  /* Inport: '<Root>/v_bus' incorporates:
   *  Outport: '<Root>/tABC'
   */
  SVPWM(rtb_Add_o, rtb_Integrator_nt, rtU.v_bus, rtY.tABC);

  /* End of Outputs for SubSystem: '<S2>/SVPWM' */

  /* DeadZone: '<S104>/DeadZone' */
  if (Integrator > 12.4707661F) {
    Integrator -= 12.4707661F;
  } else if (Integrator >= -12.4707661F) {
    Integrator = 0.0F;
  } else {
    Integrator -= -12.4707661F;
  }

  /* End of DeadZone: '<S104>/DeadZone' */

  /* Product: '<S108>/IProd Out' incorporates:
   *  Constant: '<S14>/Constant4'
   */
  rtb_IntegralGain *= CurrKPKI.CurrKi;

  /* DeadZone: '<S154>/DeadZone' */
  if (rtb_DeadZone_e > 12.4707661F) {
    rtb_DeadZone_e -= 12.4707661F;
  } else if (rtb_DeadZone_e >= -12.4707661F) {
    rtb_DeadZone_e = 0.0F;
  } else {
    rtb_DeadZone_e -= -12.4707661F;
  }

  /* End of DeadZone: '<S154>/DeadZone' */

  /* Product: '<S158>/IProd Out' incorporates:
   *  Constant: '<S14>/Constant2'
   */
  rtb_Merge1_h *= CurrKPKI.CurrKi;

  /* If: '<S70>/If1' */
  if (rtb_Saturation > 6.28318548F) {
    /* Outputs for IfAction SubSystem: '<S70>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S72>/Action Port'
     */
    /* Update for UnitDelay: '<S19>/Unit Delay' incorporates:
     *  Constant: '<S72>/2pi'
     *  Sum: '<S72>/Subtract1'
     */
    rtDW.UnitDelay_DSTATE_m = rtb_Saturation - 6.28318548F;

    /* End of Outputs for SubSystem: '<S70>/If Action Subsystem2' */
  } else if (rtb_Saturation < 0.0F) {
    /* Outputs for IfAction SubSystem: '<S70>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S73>/Action Port'
     */
    /* Update for UnitDelay: '<S19>/Unit Delay' incorporates:
     *  Constant: '<S73>/Angle_offset'
     *  Sum: '<S73>/Subtract1'
     */
    rtDW.UnitDelay_DSTATE_m = rtb_Saturation + 6.28318548F;

    /* End of Outputs for SubSystem: '<S70>/If Action Subsystem3' */
  } else {
    /* Outputs for IfAction SubSystem: '<S70>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S71>/Action Port'
     */
    /* Update for UnitDelay: '<S19>/Unit Delay' incorporates:
     *  SignalConversion generated from: '<S71>/In1'
     */
    rtDW.UnitDelay_DSTATE_m = rtb_Saturation;

    /* End of Outputs for SubSystem: '<S70>/If Action Subsystem1' */
  }

  /* End of If: '<S70>/If1' */

  /* Switch: '<S102>/Switch1' incorporates:
   *  Constant: '<S102>/Clamping_zero'
   *  Constant: '<S102>/Constant'
   *  Constant: '<S102>/Constant2'
   *  RelationalOperator: '<S102>/fix for DT propagation issue'
   */
  if (Integrator > 0.0F) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S102>/Switch2' incorporates:
   *  Constant: '<S102>/Clamping_zero'
   *  Constant: '<S102>/Constant3'
   *  Constant: '<S102>/Constant4'
   *  RelationalOperator: '<S102>/fix for DT propagation issue1'
   */
  if (rtb_IntegralGain > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S102>/Switch' incorporates:
   *  Constant: '<S102>/Clamping_zero'
   *  Constant: '<S102>/Constant1'
   *  Logic: '<S102>/AND3'
   *  RelationalOperator: '<S102>/Equal1'
   *  RelationalOperator: '<S102>/Relational Operator'
   *  Switch: '<S102>/Switch1'
   *  Switch: '<S102>/Switch2'
   */
  if ((Integrator != 0.0F) && (tmp == tmp_0)) {
    rtb_IntegralGain = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S111>/Integrator' incorporates:
   *  Switch: '<S102>/Switch'
   */
  rtDW.Integrator_DSTATE += 0.0001F * rtb_IntegralGain;

  /* Switch: '<S152>/Switch1' incorporates:
   *  Constant: '<S152>/Clamping_zero'
   *  Constant: '<S152>/Constant'
   *  Constant: '<S152>/Constant2'
   *  RelationalOperator: '<S152>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_e > 0.0F) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S152>/Switch2' incorporates:
   *  Constant: '<S152>/Clamping_zero'
   *  Constant: '<S152>/Constant3'
   *  Constant: '<S152>/Constant4'
   *  RelationalOperator: '<S152>/fix for DT propagation issue1'
   */
  if (rtb_Merge1_h > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S152>/Switch' incorporates:
   *  Constant: '<S152>/Clamping_zero'
   *  Constant: '<S152>/Constant1'
   *  Logic: '<S152>/AND3'
   *  RelationalOperator: '<S152>/Equal1'
   *  RelationalOperator: '<S152>/Relational Operator'
   *  Switch: '<S152>/Switch1'
   *  Switch: '<S152>/Switch2'
   */
  if ((rtb_DeadZone_e != 0.0F) && (tmp == tmp_0)) {
    rtb_Merge1_h = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S161>/Integrator' incorporates:
   *  Switch: '<S152>/Switch'
   */
  rtDW.Integrator_DSTATE_b += 0.0001F * rtb_Merge1_h;

  /* Update for Delay: '<S12>/Delay' */
  rtDW.Delay_DSTATE = rtb_Add1_h;

  /* Update for UnitDelay: '<S17>/Unit Delay2' */
  rtDW.UnitDelay2_DSTATE = rtb_UnitDelay3;

  /* Update for UnitDelay: '<S17>/Unit Delay3' */
  rtDW.UnitDelay3_DSTATE = rtb_UnitDelay2;

  /* Update for UnitDelay: '<S17>/Unit Delay4' */
  rtDW.UnitDelay4_DSTATE = rtb_Sign;

  /* Update for UnitDelay: '<S17>/Unit Delay5' */
  rtDW.UnitDelay5_DSTATE = rtb_Sign1;

  /* Switch: '<S44>/Switch1' incorporates:
   *  Constant: '<S44>/Clamping_zero'
   *  Constant: '<S44>/Constant'
   *  Constant: '<S44>/Constant2'
   *  RelationalOperator: '<S44>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_n > 0.0F) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S44>/Switch2' incorporates:
   *  Constant: '<S44>/Clamping_zero'
   *  Constant: '<S44>/Constant3'
   *  Constant: '<S44>/Constant4'
   *  RelationalOperator: '<S44>/fix for DT propagation issue1'
   */
  if (rtb_IntegralGain_h > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S44>/Switch' incorporates:
   *  Constant: '<S44>/Clamping_zero'
   *  Constant: '<S44>/Constant1'
   *  Logic: '<S44>/AND3'
   *  RelationalOperator: '<S44>/Equal1'
   *  RelationalOperator: '<S44>/Relational Operator'
   *  Switch: '<S44>/Switch1'
   *  Switch: '<S44>/Switch2'
   */
  if ((rtb_DeadZone_n != 0.0F) && (tmp == tmp_0)) {
    rtb_IntegralGain_h = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S53>/Integrator' incorporates:
   *  Switch: '<S44>/Switch'
   */
  rtDW.Integrator_DSTATE_o += 0.0001F * rtb_IntegralGain_h;

  /* Update for Delay: '<S15>/Delay' */
  rtDW.Delay_DSTATE_j = rtb_Add1_h;

  /* Update for UnitDelay: '<S17>/Unit Delay' */
  rtDW.UnitDelay_DSTATE_e = rtb_Sign;

  /* Update for UnitDelay: '<S17>/Unit Delay1' */
  rtDW.UnitDelay1_DSTATE_j = rtb_Sign1;

  /* End of Outputs for SubSystem: '<S1>/currloop' */
  /* End of Outputs for SubSystem: '<Root>/FOC_Model' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.001, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    rtM->Timing.clockTick1++;
  }

  rate_scheduler();
}

/* Model initialize function */
void FOC_Model_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_Model' */
  /* SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/speedloop'
   */
  /* InitializeConditions for DiscreteIntegrator: '<S213>/Integrator' */
  rtDW.Integrator_PrevResetState = 2;

  /* End of SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' */

  /* SystemInitialize for Atomic SubSystem: '<S1>/currloop' */
  /* SystemInitialize for IfAction SubSystem: '<S2>/If Action Subsystem5' */
  /* InitializeConditions for DiscreteIntegrator: '<S9>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_PrevRese = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S9>/Discrete-Time Integrator1' */
  rtDW.DiscreteTimeIntegrator1_PrevRes = 2;

  /* End of SystemInitialize for SubSystem: '<S2>/If Action Subsystem5' */
  /* End of SystemInitialize for SubSystem: '<S1>/currloop' */
  /* End of SystemInitialize for SubSystem: '<Root>/FOC_Model' */

  /* Enable for Atomic SubSystem: '<Root>/FOC_Model' */
  /* Enable for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/speedloop'
   */
  rtDW.speedloop_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S213>/Integrator' */
  rtDW.Integrator_SYSTEM_ENABLE = 1U;

  /* End of Enable for S-Function (fcgen): '<S1>/Function-Call Generator' */
  /* End of Enable for SubSystem: '<Root>/FOC_Model' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
