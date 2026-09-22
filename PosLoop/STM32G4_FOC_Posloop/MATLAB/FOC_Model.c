/*
 * File: FOC_Model.c
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

#include "FOC_Model.h"
#include "rtwtypes.h"
#include <math.h>

/* Named constants for Chart: '<S3>/Chart' */
#define IN_AlignStage                  ((uint8_T)1U)
#define IN_IDLE                        ((uint8_T)2U)
#define IN_RunStage                    ((uint8_T)3U)

/* Exported block signals */
real32_T Motor_state;                  /* '<S3>/Chart' */
real32_T PosFd;                        /* '<S2>/Add' */
real32_T SpeedFd;                      /* '<S168>/Gain' */

/* Exported data definition */

/* Definition for custom storage class: Struct */
CurrKPKI_type CurrKPKI = {
  /* CurrKi */
  2.3F,

  /* CurrKp */
  0.0008F
};

Pos_kpkikd_type Pos_kpkikd = {
  /* Pos_kp */
  5.0F
};

motor_type motor = {
  /* Pn */
  4.0F
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
static void SVPWM(real32_T rtu_Valpha, real32_T rtu_Vbeta, real32_T rtu_v_bus,
                  real32_T rty_tABC[3]);
static void rate_scheduler(void);

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

/* Output and update for atomic system: '<S3>/SVPWM' */
static void SVPWM(real32_T rtu_Valpha, real32_T rtu_Vbeta, real32_T rtu_v_bus,
                  real32_T rty_tABC[3])
{
  real32_T rtb_Min;
  real32_T rtb_Sum1_a;
  real32_T rtb_Sum_o;

  /* Gain: '<S63>/Gain' */
  rtb_Min = -0.5F * rtu_Valpha;

  /* Gain: '<S63>/Gain1' */
  rtb_Sum1_a = 0.866025388F * rtu_Vbeta;

  /* Sum: '<S63>/Sum' */
  rtb_Sum_o = rtb_Min + rtb_Sum1_a;

  /* Sum: '<S63>/Sum1' */
  rtb_Sum1_a = rtb_Min - rtb_Sum1_a;

  /* Gain: '<S64>/Gain' incorporates:
   *  MinMax: '<S64>/Min'
   *  MinMax: '<S64>/Min1'
   *  Sum: '<S64>/Sum'
   */
  rtb_Min = (fminf(fminf(rtu_Valpha, rtb_Sum_o), rtb_Sum1_a) + fmaxf(fmaxf
              (rtu_Valpha, rtb_Sum_o), rtb_Sum1_a)) * -0.5F;

  /* Sum: '<S61>/Sum' */
  rty_tABC[0] = rtb_Min + rtu_Valpha;
  rty_tABC[1] = rtb_Min + rtb_Sum_o;
  rty_tABC[2] = rtb_Min + rtb_Sum1_a;

  /* Gain: '<S61>/PWM_HalfPeriod' incorporates:
   *  Constant: '<S61>/Constant'
   *  Gain: '<S61>/Gain'
   *  Product: '<S61>/Divide'
   *  Sum: '<S61>/Sum1'
   */
  rty_tABC[0] = (-rty_tABC[0] / rtu_v_bus + 0.5F) * 8000.0F;
  rty_tABC[1] = (-rty_tABC[1] / rtu_v_bus + 0.5F) * 8000.0F;
  rty_tABC[2] = (-rty_tABC[2] / rtu_v_bus + 0.5F) * 8000.0F;
}

/* Model step function */
void FOC_Model_step(void)
{
  real32_T Integrator;
  real32_T rtb_DeadZone;
  real32_T rtb_DeadZone_d;
  real32_T rtb_IntegralGain;
  real32_T rtb_Integrator_f;
  real32_T rtb_Saturation;
  real32_T rtb_Saturation_k;
  real32_T rtb_Sum1;
  uint32_T speedloop_ELAPS_T;
  int8_T tmp;
  int8_T tmp_0;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_Model' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (fcgen): '<S1>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S1>/Pos_Loop'
     */
    /* Sum: '<S2>/Add' incorporates:
     *  Gain: '<S2>/Gain'
     *  Inport: '<Root>/Encoder_Cnt'
     *  Inport: '<Root>/Encoder_Theta'
     */
    PosFd = 6.28318501F * rtU.Encoder_Cnt + rtU.Encoder_Theta;

    /* End of Outputs for S-Function (fcgen): '<S1>/Function-Call Generator1' */

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

    /* Sum: '<S168>/Sum1' incorporates:
     *  Inport: '<Root>/Encoder_Theta'
     *  UnitDelay: '<S168>/Unit Delay'
     */
    rtb_Sum1 = rtU.Encoder_Theta - rtDW.UnitDelay_DSTATE_g;

    /* If: '<S219>/If1' incorporates:
     *  Constant: '<S221>/2pi'
     *  Constant: '<S222>/2pi'
     *  Gain: '<S168>/Gain'
     *  Gain: '<S168>/Gain1'
     *  Gain: '<S220>/Gain'
     *  Gain: '<S221>/Gain'
     *  Gain: '<S222>/Gain'
     *  Sum: '<S221>/Subtract1'
     *  Sum: '<S222>/Subtract1'
     */
    if (rtb_Sum1 > 4.2F) {
      /* Outputs for IfAction SubSystem: '<S219>/If Action Subsystem2' incorporates:
       *  ActionPort: '<S221>/Action Port'
       */
      rtb_Sum1 = (rtb_Sum1 - 6.28318501F) * 1000.0F;

      /* End of Outputs for SubSystem: '<S219>/If Action Subsystem2' */
    } else if (rtb_Sum1 < -4.2F) {
      /* Outputs for IfAction SubSystem: '<S219>/If Action Subsystem3' incorporates:
       *  ActionPort: '<S222>/Action Port'
       */
      rtb_Sum1 = (rtb_Sum1 + 6.28318501F) * 1000.0F;

      /* End of Outputs for SubSystem: '<S219>/If Action Subsystem3' */
    } else {
      /* Outputs for IfAction SubSystem: '<S219>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S220>/Action Port'
       */
      rtb_Sum1 *= 1000.0F;

      /* End of Outputs for SubSystem: '<S219>/If Action Subsystem1' */
    }

    SpeedFd = 1.0F / motor.Pn * (9.54929638F * rtb_Sum1);

    /* End of If: '<S219>/If1' */
    /* End of Outputs for S-Function (fcgen): '<S1>/Function-Call Generator' */

    /* S-Function (fcgen): '<S1>/Function-Call Generator1' incorporates:
     *  SubSystem: '<S1>/Pos_Loop'
     */
    /* Product: '<S42>/PProd Out' incorporates:
     *  Constant: '<S2>/Constant'
     *  Inport: '<Root>/PosRef'
     *  Sum: '<S2>/Sum'
     */
    rtb_Sum1 = (rtU.PosRef - PosFd) * Pos_kpkikd.Pos_kp;

    /* Saturate: '<S44>/Saturation' */
    if (rtb_Sum1 > 2000.0F) {
      rtb_Sum1 = 2000.0F;
    } else if (rtb_Sum1 < -2000.0F) {
      rtb_Sum1 = -2000.0F;
    }

    /* S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
     *  SubSystem: '<S1>/speedloop'
     */
    /* Sum: '<S4>/Sum2' incorporates:
     *  Saturate: '<S44>/Saturation'
     */
    rtb_Sum1 -= SpeedFd;

    /* End of Outputs for S-Function (fcgen): '<S1>/Function-Call Generator1' */

    /* Gain: '<S199>/Integral Gain' */
    rtb_IntegralGain = spd_kpki.spd_ki * rtb_Sum1;

    /* DiscreteIntegrator: '<S202>/Integrator' incorporates:
     *  UnitDelay: '<S1>/Unit Delay'
     */
    if (rtDW.Integrator_SYSTEM_ENABLE != 0) {
      /* DiscreteIntegrator: '<S202>/Integrator' */
      Integrator = rtDW.Integrator_DSTATE_h;
    } else if ((rtDW.SpeedReset > 0.0) && (rtDW.Integrator_PrevResetState <= 0))
    {
      /* DiscreteIntegrator: '<S202>/Integrator' */
      Integrator = 0.0F;
    } else {
      /* DiscreteIntegrator: '<S202>/Integrator' */
      Integrator = (real32_T)(0.001 * (real_T)speedloop_ELAPS_T
        * rtDW.Integrator_PREV_U) + rtDW.Integrator_DSTATE_h;
    }

    /* End of DiscreteIntegrator: '<S202>/Integrator' */

    /* Sum: '<S211>/Sum' incorporates:
     *  Gain: '<S207>/Proportional Gain'
     */
    rtb_Sum1 = spd_kpki.spd_kp * rtb_Sum1 + Integrator;

    /* DeadZone: '<S195>/DeadZone' incorporates:
     *  Saturate: '<S209>/Saturation'
     */
    if (rtb_Sum1 > 20.0F) {
      rtb_DeadZone = rtb_Sum1 - 20.0F;

      /* Saturate: '<S209>/Saturation' */
      rtDW.Saturation_j = 20.0F;
    } else {
      if (rtb_Sum1 >= -20.0F) {
        rtb_DeadZone = 0.0F;
      } else {
        rtb_DeadZone = rtb_Sum1 - -20.0F;
      }

      if (rtb_Sum1 < -20.0F) {
        /* Saturate: '<S209>/Saturation' */
        rtDW.Saturation_j = -20.0F;
      } else {
        /* Saturate: '<S209>/Saturation' */
        rtDW.Saturation_j = rtb_Sum1;
      }
    }

    /* End of DeadZone: '<S195>/DeadZone' */

    /* Update for UnitDelay: '<S168>/Unit Delay' incorporates:
     *  Inport: '<Root>/Encoder_Theta'
     */
    rtDW.UnitDelay_DSTATE_g = rtU.Encoder_Theta;

    /* Update for DiscreteIntegrator: '<S202>/Integrator' incorporates:
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

    /* Switch: '<S193>/Switch1' incorporates:
     *  Constant: '<S193>/Clamping_zero'
     *  Constant: '<S193>/Constant'
     *  Constant: '<S193>/Constant2'
     *  RelationalOperator: '<S193>/fix for DT propagation issue'
     */
    if (rtb_DeadZone > 0.0F) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    /* Switch: '<S193>/Switch2' incorporates:
     *  Constant: '<S193>/Clamping_zero'
     *  Constant: '<S193>/Constant3'
     *  Constant: '<S193>/Constant4'
     *  RelationalOperator: '<S193>/fix for DT propagation issue1'
     */
    if (rtb_IntegralGain > 0.0F) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    /* Switch: '<S193>/Switch' incorporates:
     *  Constant: '<S193>/Clamping_zero'
     *  Logic: '<S193>/AND3'
     *  RelationalOperator: '<S193>/Equal1'
     *  RelationalOperator: '<S193>/Relational Operator'
     *  Switch: '<S193>/Switch1'
     *  Switch: '<S193>/Switch2'
     */
    if ((rtb_DeadZone != 0.0F) && (tmp == tmp_0)) {
      /* Update for DiscreteIntegrator: '<S202>/Integrator' incorporates:
       *  Constant: '<S193>/Constant1'
       */
      rtDW.Integrator_PREV_U = 0.0F;
    } else {
      /* Update for DiscreteIntegrator: '<S202>/Integrator' */
      rtDW.Integrator_PREV_U = rtb_IntegralGain;
    }

    /* End of Switch: '<S193>/Switch' */
    /* End of Outputs for S-Function (fcgen): '<S1>/Function-Call Generator' */
  }

  /* Outputs for Atomic SubSystem: '<S1>/currloop' */
  /* Chart: '<S3>/Chart' incorporates:
   *  Inport: '<Root>/Motor_OnOff'
   */
  if (rtDW.temporalCounter_i1 < 2047U) {
    rtDW.temporalCounter_i1++;
  }

  if (rtDW.is_active_c3_FOC_Model == 0U) {
    rtDW.is_active_c3_FOC_Model = 1U;
    rtDW.is_c3_FOC_Model = IN_IDLE;
  } else {
    switch (rtDW.is_c3_FOC_Model) {
     case IN_AlignStage:
      if (rtDW.temporalCounter_i1 >= 2000) {
        rtDW.is_c3_FOC_Model = IN_RunStage;
      } else if (rtU.Motor_OnOff == 0.0F) {
        rtDW.is_c3_FOC_Model = IN_IDLE;
      } else {
        Motor_state = 2.0F;
      }
      break;

     case IN_IDLE:
      if (rtU.Motor_OnOff == 1.0F) {
        rtDW.temporalCounter_i1 = 0U;
        rtDW.is_c3_FOC_Model = IN_AlignStage;
        rtDW.SpeedReset = 0.0;
      } else {
        Motor_state = 1.0F;
      }
      break;

     default:
      /* case IN_RunStage: */
      if (rtU.Motor_OnOff == 0.0F) {
        rtDW.is_c3_FOC_Model = IN_IDLE;
      } else {
        Motor_state = 3.0F;
        rtDW.SpeedReset = 1.0;
      }
      break;
    }
  }

  /* End of Chart: '<S3>/Chart' */

  /* SwitchCase: '<S3>/Switch Case' */
  switch ((int32_T)Motor_state) {
   case 1:
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S57>/Action Port'
     */
    /* Merge: '<S3>/Merge' incorporates:
     *  Constant: '<S57>/Constant'
     *  SignalConversion generated from: '<S57>/theta_fd'
     */
    rtDW.Merge = 0.0F;

    /* Merge: '<S3>/Merge1' incorporates:
     *  Constant: '<S57>/Constant1'
     *  SignalConversion generated from: '<S57>/iq_ref'
     */
    rtDW.Merge1 = 0.0F;

    /* Merge: '<S3>/Merge2' incorporates:
     *  Constant: '<S57>/Constant2'
     *  SignalConversion generated from: '<S57>/id_ref'
     */
    rtDW.Merge2 = 0.0F;

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S58>/Action Port'
     */
    /* Merge: '<S3>/Merge' incorporates:
     *  Constant: '<S58>/Constant'
     *  SignalConversion generated from: '<S58>/theta_fd'
     */
    rtDW.Merge = 0.0F;

    /* Merge: '<S3>/Merge1' incorporates:
     *  Constant: '<S58>/Constant1'
     *  SignalConversion generated from: '<S58>/iq_ref'
     */
    rtDW.Merge1 = 0.0F;

    /* Merge: '<S3>/Merge2' incorporates:
     *  Constant: '<S58>/Constant2'
     *  SignalConversion generated from: '<S58>/id_ref'
     */
    rtDW.Merge2 = 2.0F;

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem1' */
    break;

   case 3:
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S59>/Action Port'
     */
    /* Merge: '<S3>/Merge2' incorporates:
     *  Constant: '<S59>/Constant2'
     *  SignalConversion generated from: '<S59>/id_ref'
     */
    rtDW.Merge2 = 0.0F;

    /* Merge: '<S3>/Merge' incorporates:
     *  Inport: '<Root>/Encoder_Theta'
     *  SignalConversion generated from: '<S59>/Encoder_Theta'
     */
    rtDW.Merge = rtU.Encoder_Theta;

    /* Merge: '<S3>/Merge1' incorporates:
     *  SignalConversion generated from: '<S59>/iq'
     */
    rtDW.Merge1 = rtDW.Saturation_j;

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem2' */
    break;
  }

  /* End of SwitchCase: '<S3>/Switch Case' */

  /* Trigonometry: '<S3>/SinCos1' */
  rtb_Sum1 = cosf(rtDW.Merge);

  /* Sum: '<S56>/Add1' incorporates:
   *  Gain: '<S56>/Gain'
   *  Gain: '<S56>/Gain1'
   *  Inport: '<Root>/ia'
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   *  Sum: '<S56>/Add'
   */
  rtb_Integrator_f = 0.666666687F * rtU.ia - (rtU.ib + rtU.ic) * 0.333333343F;

  /* Gain: '<S56>/Gain2' incorporates:
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   *  Sum: '<S56>/Add2'
   */
  rtb_IntegralGain = (rtU.ib - rtU.ic) * 0.577350259F;

  /* Trigonometry: '<S3>/SinCos' */
  Integrator = sinf(rtDW.Merge);

  /* Sum: '<S62>/Sum1' incorporates:
   *  Product: '<S60>/Product'
   *  Product: '<S60>/Product1'
   *  Sum: '<S60>/Add'
   */
  rtb_DeadZone = rtDW.Merge2 - (rtb_Integrator_f * rtb_Sum1 + rtb_IntegralGain *
    Integrator);

  /* Sum: '<S109>/Sum' incorporates:
   *  Constant: '<S62>/Constant3'
   *  DiscreteIntegrator: '<S100>/Integrator'
   *  Product: '<S105>/PProd Out'
   */
  rtb_DeadZone_d = rtb_DeadZone * CurrKPKI.CurrKp + rtDW.Integrator_DSTATE;

  /* Saturate: '<S107>/Saturation' */
  if (rtb_DeadZone_d > 12.4707661F) {
    rtb_Saturation = 12.4707661F;
  } else if (rtb_DeadZone_d < -12.4707661F) {
    rtb_Saturation = -12.4707661F;
  } else {
    rtb_Saturation = rtb_DeadZone_d;
  }

  /* End of Saturate: '<S107>/Saturation' */

  /* Sum: '<S62>/Sum7' incorporates:
   *  Product: '<S60>/Product2'
   *  Product: '<S60>/Product3'
   *  Sum: '<S60>/Add1'
   */
  rtb_IntegralGain = rtDW.Merge1 - (rtb_IntegralGain * rtb_Sum1 -
    rtb_Integrator_f * Integrator);

  /* Sum: '<S159>/Sum' incorporates:
   *  Constant: '<S62>/Constant1'
   *  DiscreteIntegrator: '<S150>/Integrator'
   *  Product: '<S155>/PProd Out'
   */
  rtb_Integrator_f = rtb_IntegralGain * CurrKPKI.CurrKp +
    rtDW.Integrator_DSTATE_b;

  /* Saturate: '<S157>/Saturation' */
  if (rtb_Integrator_f > 12.4707661F) {
    rtb_Saturation_k = 12.4707661F;
  } else if (rtb_Integrator_f < -12.4707661F) {
    rtb_Saturation_k = -12.4707661F;
  } else {
    rtb_Saturation_k = rtb_Integrator_f;
  }

  /* End of Saturate: '<S157>/Saturation' */

  /* Outputs for Atomic SubSystem: '<S3>/SVPWM' */
  /* Sum: '<S54>/Add' incorporates:
   *  Inport: '<Root>/v_bus'
   *  Outport: '<Root>/tABC'
   *  Product: '<S54>/Product'
   *  Product: '<S54>/Product1'
   *  Product: '<S54>/Product2'
   *  Product: '<S54>/Product3'
   *  Sum: '<S54>/Add1'
   */
  SVPWM(rtb_Saturation * rtb_Sum1 - rtb_Saturation_k * Integrator,
        rtb_Saturation * Integrator + rtb_Saturation_k * rtb_Sum1, rtU.v_bus,
        rtY.tABC);

  /* End of Outputs for SubSystem: '<S3>/SVPWM' */

  /* DeadZone: '<S143>/DeadZone' */
  if (rtb_Integrator_f > 12.4707661F) {
    rtb_Integrator_f -= 12.4707661F;
  } else if (rtb_Integrator_f >= -12.4707661F) {
    rtb_Integrator_f = 0.0F;
  } else {
    rtb_Integrator_f -= -12.4707661F;
  }

  /* End of DeadZone: '<S143>/DeadZone' */

  /* Product: '<S147>/IProd Out' incorporates:
   *  Constant: '<S62>/Constant2'
   */
  rtb_IntegralGain *= CurrKPKI.CurrKi;

  /* DeadZone: '<S93>/DeadZone' */
  if (rtb_DeadZone_d > 12.4707661F) {
    rtb_DeadZone_d -= 12.4707661F;
  } else if (rtb_DeadZone_d >= -12.4707661F) {
    rtb_DeadZone_d = 0.0F;
  } else {
    rtb_DeadZone_d -= -12.4707661F;
  }

  /* End of DeadZone: '<S93>/DeadZone' */

  /* Product: '<S97>/IProd Out' incorporates:
   *  Constant: '<S62>/Constant4'
   */
  rtb_DeadZone *= CurrKPKI.CurrKi;

  /* Switch: '<S91>/Switch1' incorporates:
   *  Constant: '<S91>/Clamping_zero'
   *  Constant: '<S91>/Constant'
   *  Constant: '<S91>/Constant2'
   *  RelationalOperator: '<S91>/fix for DT propagation issue'
   */
  if (rtb_DeadZone_d > 0.0F) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S91>/Switch2' incorporates:
   *  Constant: '<S91>/Clamping_zero'
   *  Constant: '<S91>/Constant3'
   *  Constant: '<S91>/Constant4'
   *  RelationalOperator: '<S91>/fix for DT propagation issue1'
   */
  if (rtb_DeadZone > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S91>/Switch' incorporates:
   *  Constant: '<S91>/Clamping_zero'
   *  Constant: '<S91>/Constant1'
   *  Logic: '<S91>/AND3'
   *  RelationalOperator: '<S91>/Equal1'
   *  RelationalOperator: '<S91>/Relational Operator'
   *  Switch: '<S91>/Switch1'
   *  Switch: '<S91>/Switch2'
   */
  if ((rtb_DeadZone_d != 0.0F) && (tmp == tmp_0)) {
    rtb_DeadZone = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S100>/Integrator' incorporates:
   *  Switch: '<S91>/Switch'
   */
  rtDW.Integrator_DSTATE += 0.0001F * rtb_DeadZone;

  /* Switch: '<S141>/Switch1' incorporates:
   *  Constant: '<S141>/Clamping_zero'
   *  Constant: '<S141>/Constant'
   *  Constant: '<S141>/Constant2'
   *  RelationalOperator: '<S141>/fix for DT propagation issue'
   */
  if (rtb_Integrator_f > 0.0F) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S141>/Switch2' incorporates:
   *  Constant: '<S141>/Clamping_zero'
   *  Constant: '<S141>/Constant3'
   *  Constant: '<S141>/Constant4'
   *  RelationalOperator: '<S141>/fix for DT propagation issue1'
   */
  if (rtb_IntegralGain > 0.0F) {
    tmp_0 = 1;
  } else {
    tmp_0 = -1;
  }

  /* Switch: '<S141>/Switch' incorporates:
   *  Constant: '<S141>/Clamping_zero'
   *  Constant: '<S141>/Constant1'
   *  Logic: '<S141>/AND3'
   *  RelationalOperator: '<S141>/Equal1'
   *  RelationalOperator: '<S141>/Relational Operator'
   *  Switch: '<S141>/Switch1'
   *  Switch: '<S141>/Switch2'
   */
  if ((rtb_Integrator_f != 0.0F) && (tmp == tmp_0)) {
    rtb_IntegralGain = 0.0F;
  }

  /* Update for DiscreteIntegrator: '<S150>/Integrator' incorporates:
   *  Switch: '<S141>/Switch'
   */
  rtDW.Integrator_DSTATE_b += 0.0001F * rtb_IntegralGain;

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
  /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_Model' */
  /* SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/speedloop'
   */
  /* InitializeConditions for DiscreteIntegrator: '<S202>/Integrator' */
  rtDW.Integrator_PrevResetState = 2;

  /* End of SystemInitialize for S-Function (fcgen): '<S1>/Function-Call Generator' */
  /* End of SystemInitialize for SubSystem: '<Root>/FOC_Model' */

  /* Enable for Atomic SubSystem: '<Root>/FOC_Model' */
  /* Enable for S-Function (fcgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/speedloop'
   */
  rtDW.speedloop_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S202>/Integrator' */
  rtDW.Integrator_SYSTEM_ENABLE = 1U;

  /* End of Enable for S-Function (fcgen): '<S1>/Function-Call Generator' */
  /* End of Enable for SubSystem: '<Root>/FOC_Model' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
