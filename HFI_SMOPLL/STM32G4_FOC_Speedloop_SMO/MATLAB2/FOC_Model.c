/*
 * File: FOC_Model.c
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

#include "FOC_Model.h"
#include "rtwtypes.h"
#include <math.h>
#include <float.h>
#include "math.h"

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

/* Forward declaration for local functions */
static real32_T mod(real32_T x);
static void rate_scheduler(void);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
real_T rtNaN = -(real_T)NAN;
real_T rtInf = (real_T)INFINITY;
real_T rtMinusInf = -(real_T)INFINITY;
real32_T rtNaNF = -(real32_T)NAN;
real32_T rtInfF = (real32_T)INFINITY;
real32_T rtMinusInfF = -(real32_T)INFINITY;

/* Return rtNaN needed by the generated code. */
static real_T rtGetNaN(void)
{
  return rtNaN;
}

/* Return rtNaNF needed by the generated code. */
static real32_T rtGetNaNF(void)
{
  return rtNaNF;
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
  return (boolean_T)(isnan(value) != 0);
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  return (boolean_T)(isnan(value) != 0);
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

/* Function for MATLAB Function: '<S4>/MATLAB Function' */
static real32_T mod(real32_T x)
{
  real32_T r;
  if (rtIsNaNF(x)) {
    r = (rtNaNF);
  } else if (rtIsInfF(x)) {
    r = (rtNaNF);
  } else if (x == 0.0F) {
    r = 0.0F;
  } else {
    boolean_T rEQ0;
    r = fmodf(x, 6.28318548F);
    rEQ0 = (r == 0.0F);
    if (!rEQ0) {
      real32_T q;
      q = fabsf(x / 6.28318548F);
      rEQ0 = !(fabsf(q - floorf(q + 0.5F)) > 1.1920929E-7F * q);
    }

    if (rEQ0) {
      r = 0.0F;
    } else if (x < 0.0F) {
      r += 6.28318548F;
    }
  }

  return r;
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
  real_T rtb_Saturation;
  real_T rtb_dbA;
  int32_T rtb_startup_ready;
  int32_T sector;
  real32_T DiscreteFilter3_tmp_e;
  real32_T DiscreteFilter3_tmp_e_e;
  real32_T DiscreteFilter3_tmp_e_p;
  real32_T T2;
  real32_T dtheta;
  real32_T lambda_target;
  real32_T rtb_Abs;
  real32_T rtb_Add;
  real32_T rtb_Delay;
  real32_T rtb_Delay2;
  real32_T rtb_DiscreteFilter5;
  real32_T rtb_DiscreteTimeIntegrator1;
  real32_T rtb_DiscreteTimeIntegrator_e;
  real32_T rtb_Fcn1;
  real32_T rtb_Gain5;
  real32_T rtb_Gain6_l;
  real32_T rtb_IntegralGain_m;
  real32_T rtb_MultiportSwitch;
  real32_T rtb_Product1_f;
  real32_T rtb_Product_e;
  real32_T rtb_Saturation_f;
  real32_T rtb_SumI2_h;
  real32_T rtb_Sum_p;
  real32_T rtb_Tcmp2;
  real32_T rtb_Tsamp_f;
  real32_T rtb_alg_reset;
  real32_T rtb_alpha;
  real32_T rtb_beta;
  real32_T rtb_flag;
  real32_T rtb_hfi_ready;
  real32_T rtb_id_ref;
  real32_T rtb_n;
  real32_T rtb_neg_enable;
  real32_T rtb_pos_enable;
  real32_T rtb_q;
  real32_T rtb_speed_enable;
  real32_T ta;
  uint32_T rtb_DataTypeConversion1;
  boolean_T estimate_valid;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_Model' */
  /* RateTransition: '<S1>/Rate Transition2' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* RateTransition: '<S1>/Rate Transition2' */
    rtDW.RateTransition2 = rtDW.RateTransition2_Buffer0;
  }

  /* End of RateTransition: '<S1>/Rate Transition2' */

  /* MATLAB Function: '<S1>/StartupManager' incorporates:
   *  Inport: '<Root>/ControlEnable'
   *  Inport: '<Root>/FaultActive'
   *  Inport: '<Root>/Reset'
   */
  rtb_id_ref = 0.0F;
  rtb_pos_enable = 0.0F;
  rtb_neg_enable = 0.0F;
  rtb_speed_enable = 0.0F;
  rtb_startup_ready = 0;
  rtb_alg_reset = 0.0F;
  if ((rtU.Reset > 0.5F) || (rtU.FaultActive > 0.5F) || (rtU.ControlEnable <
       0.5F)) {
    rtDW.state = 0U;
    rtDW.count = 0U;
    rtb_alg_reset = 1.0F;
  } else {
    switch (rtDW.state) {
     case 0U:
      rtb_alg_reset = 1.0F;
      rtDW.state = 1U;
      rtDW.count = 0U;
      break;

     case 1U:
      if (rtDW.count >= 999) {
        rtDW.state = 2U;
        rtDW.count = 0U;
      } else {
        rtDW.count++;
      }
      break;

     case 2U:
      rtb_id_ref = 2.0F;
      rtb_pos_enable = 1.0F;
      if (rtDW.count >= 99) {
        rtDW.state = 3U;
        rtDW.count = 0U;
      } else {
        rtDW.count++;
      }
      break;

     case 3U:
      if (rtDW.count >= 199) {
        rtDW.state = 4U;
        rtDW.count = 0U;
      } else {
        rtDW.count++;
      }
      break;

     case 4U:
      rtb_id_ref = -2.0F;
      rtb_neg_enable = 1.0F;
      if (rtDW.count >= 99) {
        rtDW.state = 5U;
        rtDW.count = 0U;
      } else {
        rtDW.count++;
      }
      break;

     case 5U:
      if (rtDW.count >= 99) {
        rtDW.state = 6U;
        rtDW.count = 0U;
      } else {
        rtDW.count++;
      }
      break;

     case 6U:
      rtDW.state = 7U;
      rtDW.count = 0U;
      break;

     case 7U:
      if (rtDW.count >= 498) {
        rtDW.state = 8U;
        rtDW.count = 0U;
      } else {
        rtDW.count++;
      }
      break;

     case 8U:
      rtb_speed_enable = 1.0F;
      if (rtDW.count >= 999) {
        rtDW.state = 9U;
        rtDW.count = 0U;
      } else {
        rtDW.count++;
      }
      break;

     default:
      rtDW.state = 9U;
      rtb_speed_enable = 1.0F;
      rtb_startup_ready = 1;
      rtDW.count = 0U;
      break;
    }
  }

  /* Outputs for Atomic SubSystem: '<S1>/currloop' */
  /* DiscreteIntegrator: '<S21>/PositiveResponseIntegrator' */
  if ((rtb_alg_reset != 0.0F) || (rtDW.PositiveResponseIntegrator_Prev != 0)) {
    rtDW.PositiveResponseIntegrator_DSTA = 0.0F;
  }

  /* End of DiscreteIntegrator: '<S21>/PositiveResponseIntegrator' */

  /* DiscreteIntegrator: '<S21>/NegativeResponseIntegrator' */
  if ((rtb_alg_reset != 0.0F) || (rtDW.NegativeResponseIntegrator_Prev != 0)) {
    rtDW.NegativeResponseIntegrator_DSTA = 0.0F;
  }

  /* End of DiscreteIntegrator: '<S21>/NegativeResponseIntegrator' */

  /* Sum: '<S4>/Add' incorporates:
   *  DiscreteIntegrator: '<S17>/Discrete-Time Integrator'
   */
  rtb_Add = rtDW.DiscreteTimeIntegrator_DSTATE;

  /* Fcn: '<S7>/alpha' incorporates:
   *  Inport: '<Root>/ia'
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   */
  rtb_alpha = (rtU.ia - (rtU.ib + rtU.ic) * 0.5F) * 2.0F / 3.0F;

  /* Fcn: '<S7>/beta' incorporates:
   *  Inport: '<Root>/ib'
   *  Inport: '<Root>/ic'
   */
  rtb_beta = (rtU.ib - rtU.ic) * 0.866025388F * 2.0F / 3.0F;

  /* MATLAB Function: '<S4>/MATLAB Function' incorporates:
   *  UnitDelay: '<S4>/Unit Delay'
   *  UnitDelay: '<S4>/Unit Delay1'
   *  UnitDelay: '<S4>/Unit Delay2'
   *  UnitDelay: '<S4>/Unit Delay3'
   */
  dtheta = mod((rtDW.UnitDelay2_DSTATE - rtDW.UnitDelay3_DSTATE) + 3.14159274F)
    - 3.14159274F;
  estimate_valid = ((fabsf(dtheta) < 0.52359879F) && (fabsf
    (rtDW.UnitDelay_DSTATE - rtDW.UnitDelay1_DSTATE) < 150.0F));
  if (rtb_startup_ready < 0.5F) {
    rtDW.mode = 0U;
    rtDW.lambda_mem = 0.0F;
    rtDW.enter_count = 0U;
    rtDW.exit_count = 0U;
    rtDW.valid_count = 0U;
    rtDW.wake_count = 0U;
    rtb_flag = 0.0F;
    rtb_hfi_ready = 1.0F;
    rtDW.theta_prev = rtDW.UnitDelay3_DSTATE;
  } else {
    switch (rtDW.mode) {
     case 0U:
      rtDW.lambda_mem = 0.0F;
      rtb_flag = 0.0F;
      rtb_hfi_ready = 1.0F;
      if (fabsf(rtDW.UnitDelay1_DSTATE) >= 300.0F) {
        if (estimate_valid) {
          if (rtDW.enter_count < 100) {
            rtDW.enter_count++;
          }
        } else {
          rtDW.enter_count = 0U;
        }
      } else {
        rtDW.enter_count = 0U;
      }

      if (rtDW.enter_count >= 100) {
        rtDW.mode = 1U;
        rtDW.enter_count = 0U;
        rtDW.valid_count = 0U;
      }
      break;

     case 1U:
      rtb_hfi_ready = 1.0F;
      rtb_n = fabsf(rtDW.UnitDelay1_DSTATE);
      lambda_target = 0.5F - cosf(fminf(fmaxf((rtb_n - 300.0F) / 400.0F, 0.0F),
        1.0F) * 3.14159274F) * 0.5F;
      if (estimate_valid) {
        if (rtDW.lambda_mem < lambda_target) {
          rtDW.lambda_mem = fminf(rtDW.lambda_mem + 0.00199999986F,
            lambda_target);
        } else if (rtDW.lambda_mem > lambda_target) {
          rtDW.lambda_mem = fmaxf(rtDW.lambda_mem - 0.00199999986F,
            lambda_target);
        }
      } else {
        rtDW.lambda_mem = fmaxf(rtDW.lambda_mem - 0.00199999986F, 0.0F);
      }

      if (rtDW.lambda_mem <= 0.5F) {
        rtb_flag = 0.0F;
      } else {
        rtb_flag = 0.5F - cosf(fminf(fmaxf((rtDW.lambda_mem - 0.5F) / 0.5F, 0.0F),
          1.0F) * 3.14159274F) * 0.5F;
      }

      if (rtDW.lambda_mem >= 0.999F) {
        if (fabsf(rtDW.UnitDelay_DSTATE) >= 700.0F) {
          if (estimate_valid) {
            if (rtDW.valid_count < 50) {
              rtDW.valid_count++;
            }
          } else {
            rtDW.valid_count = 0U;
          }
        } else {
          rtDW.valid_count = 0U;
        }
      } else {
        rtDW.valid_count = 0U;
      }

      if (rtDW.valid_count >= 50) {
        rtDW.mode = 2U;
        rtDW.lambda_mem = 1.0F;
        rtDW.valid_count = 0U;
        rtDW.exit_count = 0U;
        rtb_flag = 1.0F;
        rtb_hfi_ready = 0.0F;
      }

      if ((rtb_n < 300.0F) && (rtDW.lambda_mem <= 0.001F)) {
        rtDW.mode = 0U;
        rtDW.lambda_mem = 0.0F;
        rtDW.enter_count = 0U;
        rtDW.valid_count = 0U;
      }
      break;

     case 2U:
      rtDW.lambda_mem = 1.0F;
      rtb_flag = 1.0F;
      rtb_hfi_ready = 0.0F;
      if (fabsf(rtDW.UnitDelay_DSTATE) < 550.0F) {
        if (rtDW.exit_count < 100) {
          rtDW.exit_count++;
        }
      } else {
        rtDW.exit_count = 0U;
      }

      if (rtDW.exit_count >= 100) {
        rtDW.mode = 3U;
        rtDW.exit_count = 0U;
        rtDW.wake_count = 0U;
        rtDW.valid_count = 0U;
        rtDW.enter_count = 0U;
      }
      break;

     case 3U:
      rtDW.lambda_mem = 1.0F;
      rtb_hfi_ready = 0.0F;
      if (rtDW.wake_count < 200) {
        rtDW.wake_count++;
      }

      rtb_flag = 1.0F - (0.5F - cosf(fminf((real32_T)rtDW.wake_count / 200.0F,
        1.0F) * 3.14159274F) * 0.5F);
      if (fabsf(rtDW.UnitDelay_DSTATE) >= 700.0F) {
        if (rtDW.enter_count < 100) {
          rtDW.enter_count++;
        }
      } else {
        rtDW.enter_count = 0U;
      }

      if (rtDW.enter_count >= 100) {
        rtDW.mode = 2U;
        rtb_flag = 1.0F;
        rtDW.enter_count = 0U;
        rtDW.wake_count = 0U;
        rtDW.valid_count = 0U;
      } else if (rtDW.wake_count >= 200) {
        rtb_flag = 0.0F;
        if (estimate_valid) {
          if (rtDW.valid_count < 50) {
            rtDW.valid_count++;
          }
        } else {
          rtDW.valid_count = 0U;
        }

        if (rtDW.valid_count >= 50) {
          rtDW.mode = 4U;
          rtb_hfi_ready = 1.0F;
          rtDW.valid_count = 0U;
        }
      }
      break;

     case 4U:
      rtb_flag = 0.0F;
      rtb_hfi_ready = 1.0F;
      if (estimate_valid) {
        rtDW.lambda_mem = fmaxf(rtDW.lambda_mem - 0.00199999986F, 0.0F);
      } else {
        rtDW.mode = 3U;
        rtDW.lambda_mem = 1.0F;
        rtDW.wake_count = 200U;
        rtDW.valid_count = 0U;
        rtb_hfi_ready = 0.0F;
      }

      if (rtDW.lambda_mem <= 0.001F) {
        rtDW.mode = 0U;
        rtDW.lambda_mem = 0.0F;
        rtDW.enter_count = 0U;
        rtDW.valid_count = 0U;
      }
      break;

     default:
      rtDW.mode = 0U;
      rtDW.lambda_mem = 0.0F;
      rtDW.enter_count = 0U;
      rtDW.exit_count = 0U;
      rtDW.valid_count = 0U;
      rtDW.wake_count = 0U;
      rtb_flag = 0.0F;
      rtb_hfi_ready = 1.0F;
      break;
    }
  }

  rtb_n = (1.0F - rtDW.lambda_mem) * rtDW.UnitDelay1_DSTATE + rtDW.lambda_mem *
    rtDW.UnitDelay_DSTATE;
  dtheta = (mod((mod(rtDW.lambda_mem * dtheta + rtDW.UnitDelay3_DSTATE) - mod
                 (rtDW.theta_prev)) + 3.14159274F) - 3.14159274F) +
    rtDW.theta_prev;
  rtDW.theta_prev = dtheta;
  dtheta = mod(dtheta);

  /* Fcn: '<S13>/d' incorporates:
   *  Fcn: '<S13>/q'
   *  Fcn: '<S6>/Fcn'
   *  Fcn: '<S6>/Fcn1'
   */
  rtb_Fcn1 = sinf(dtheta);
  rtb_Tcmp2 = cosf(dtheta);
  lambda_target = rtb_alpha * rtb_Tcmp2 + rtb_beta * rtb_Fcn1;

  /* Gain: '<S20>/Gain5' incorporates:
   *  Delay: '<S20>/Delay'
   *  Delay: '<S20>/Delay1'
   *  Gain: '<S20>/Gain3'
   *  Sum: '<S20>/Add'
   */
  rtb_Delay2 = ((2.0F * rtDW.Delay_DSTATE + rtDW.Delay1_DSTATE[0]) +
                lambda_target) * 0.25F;

  /* Fcn: '<S13>/q' */
  rtb_q = -rtb_alpha * rtb_Fcn1 + rtb_beta * rtb_Tcmp2;

  /* Gain: '<S20>/Gain6' incorporates:
   *  Delay: '<S20>/Delay2'
   *  Delay: '<S20>/Delay3'
   *  Gain: '<S20>/Gain4'
   *  Sum: '<S20>/Add1'
   */
  rtb_Delay = ((2.0F * rtDW.Delay2_DSTATE + rtDW.Delay3_DSTATE[0]) + rtb_q) *
    0.25F;

  /* MultiPortSwitch: '<S134>/Multiport Switch' incorporates:
   *  Constant: '<S134>/ '
   *  Constant: '<S134>/Constant1'
   *  Constant: '<S134>/Constant2'
   *  Constant: '<S134>/Constant3'
   *  Constant: '<S134>/Constant4'
   *  Gain: '<S134>/Gain'
   *  Gain: '<S134>/Gain1'
   *  RelationalOperator: '<S134>/Relational Operator'
   *  RelationalOperator: '<S134>/Relational Operator1'
   *  RelationalOperator: '<S134>/Relational Operator2'
   *  Sum: '<S134>/Add1'
   */
  switch ((((rtb_Delay == 0.0F) << 2) + ((rtb_Delay > 0.0F) << 1)) + (rtb_Delay <
           0.0F)) {
   case 1:
    rtb_MultiportSwitch = 4.71238899F;
    break;

   case 2:
    rtb_MultiportSwitch = 1.57079637F;
    break;

   case 3:
    rtb_MultiportSwitch = 0.0F;
    break;

   default:
    rtb_MultiportSwitch = 0.0F;
    break;
  }

  /* End of MultiPortSwitch: '<S134>/Multiport Switch' */

  /* If: '<S133>/If1' incorporates:
   *  Constant: '<S133>/Constant'
   *  Constant: '<S133>/Constant1'
   *  Constant: '<S133>/Constant2'
   *  Constant: '<S133>/Constant3'
   *  If: '<S133>/If2'
   *  SignalConversion generated from: '<S139>/In1'
   *  SignalConversion generated from: '<S140>/In1'
   *  SignalConversion generated from: '<S141>/In1'
   *  SignalConversion generated from: '<S142>/In1'
   */
  if (rtb_Delay2 <= 0.0F) {
    /* Outputs for IfAction SubSystem: '<S133>/id<=0' incorporates:
     *  ActionPort: '<S141>/Action Port'
     */
    ta = 3.14159274F;

    /* End of Outputs for SubSystem: '<S133>/id<=0' */

    /* Outputs for IfAction SubSystem: '<S133>/id1<=0' incorporates:
     *  ActionPort: '<S139>/Action Port'
     */
    rtb_DiscreteTimeIntegrator_e = 3.14159274F;

    /* End of Outputs for SubSystem: '<S133>/id1<=0' */
  } else {
    /* Outputs for IfAction SubSystem: '<S133>/id>0' incorporates:
     *  ActionPort: '<S142>/Action Port'
     */
    ta = 0.0F;

    /* End of Outputs for SubSystem: '<S133>/id>0' */

    /* Outputs for IfAction SubSystem: '<S133>/id1>0' incorporates:
     *  ActionPort: '<S140>/Action Port'
     */
    rtb_DiscreteTimeIntegrator_e = 6.28318548F;

    /* End of Outputs for SubSystem: '<S133>/id1>0' */
  }

  /* If: '<S24>/If' incorporates:
   *  Constant: '<S24>/Constant2'
   *  Math: '<S24>/Mod1'
   *  Sum: '<S24>/Add'
   */
  if (rtb_Delay2 != 0.0F) {
    /* If: '<S133>/If' incorporates:
     *  If: '<S133>/If1'
     *  If: '<S133>/If2'
     *  Product: '<S133>/Divide'
     *  Sum: '<S133>/Add'
     *  Sum: '<S133>/Add1'
     *  Trigonometry: '<S133>/atan'
     */
    if (rtb_Delay > 0.0F) {
      rtb_MultiportSwitch = atanf(rtb_Delay / rtb_Delay2) + ta;
    } else {
      rtb_MultiportSwitch = atanf(rtb_Delay / rtb_Delay2) +
        rtb_DiscreteTimeIntegrator_e;
    }

    /* End of If: '<S133>/If' */
  }

  rtb_DiscreteTimeIntegrator_e = rt_modf_snf(rtb_MultiportSwitch + dtheta,
    6.28318548F);

  /* End of If: '<S24>/If' */

  /* Sum: '<S23>/Subtract' incorporates:
   *  Constant: '<S23>/Te2'
   *  Constant: '<S23>/Te3'
   *  DataTypeConversion: '<S23>/Data Type Conversion'
   *  Product: '<S23>/Divide'
   *  Product: '<S23>/Divide1'
   */
  rtb_dbA = rtb_DiscreteTimeIntegrator_e - (real_T)(uint32_T)
    (rtb_DiscreteTimeIntegrator_e / 6.2831853071795862) * 6.2831853071795862;

  /* DataTypeConversion: '<S23>/Data Type Conversion1' incorporates:
   *  Constant: '<S23>/Te1'
   *  Product: '<S23>/Divide2'
   */
  rtb_DataTypeConversion1 = (uint32_T)(rtb_dbA / 1.0471975511965976);

  /* Product: '<S23>/Divide4' incorporates:
   *  Constant: '<S23>/Te4'
   *  Constant: '<S23>/Te5'
   *  Constant: '<S4>/Constant4'
   *  Constant: '<S4>/IdRef3'
   *  Product: '<S23>/Divide3'
   *  Sum: '<S23>/Subtract1'
   *  Sum: '<S23>/Subtract2'
   */
  rtb_Saturation = ((rtb_dbA - (real_T)rtb_DataTypeConversion1 *
                     1.0471975511965976) - 0.52359877559829882) /
    0.10471975511965977 * 1.0E-6;

  /* Saturate: '<S23>/Saturation' */
  if (rtb_Saturation > 8.0E-7) {
    rtb_Saturation = 8.0E-7;
  } else if (rtb_Saturation < -8.0E-7) {
    rtb_Saturation = -8.0E-7;
  }

  /* End of Saturate: '<S23>/Saturation' */

  /* MultiPortSwitch: '<S23>/dbB' incorporates:
   *  Constant: '<S4>/Constant4'
   *  Gain: '<S23>/ 2'
   */
  switch (rtb_DataTypeConversion1) {
   case 0:
    rtb_dbA = rtb_Saturation;
    break;

   case 1:
    rtb_dbA = 1.0E-6;
    break;

   case 2:
    rtb_dbA = 1.0E-6;
    break;

   case 3:
    rtb_dbA = -rtb_Saturation;
    break;

   case 4:
    rtb_dbA = -1.0E-6;
    break;

   default:
    rtb_dbA = -1.0E-6;
    break;
  }

  /* End of MultiPortSwitch: '<S23>/dbB' */

  /* Sum: '<S4>/Sum4' */
  rtb_Delay2 = rtb_id_ref - rtb_Delay2;

  /* Switch: '<S4>/Switch' incorporates:
   *  Constant: '<S4>/Constant'
   *  Constant: '<S4>/Constant2'
   *  UnitDelay: '<S8>/Output'
   */
  if (rtDW.Output_DSTATE >= 1) {
    ta = 2.4F;
  } else {
    ta = -2.4F;
  }

  /* Product: '<S4>/Product' incorporates:
   *  Constant: '<S4>/Constant1'
   *  Sum: '<S4>/Sum1'
   *  Switch: '<S4>/Switch'
   */
  rtb_flag = (1.0F - rtb_flag) * ta;

  /* Sum: '<S10>/Sum6' incorporates:
   *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
   *  Gain: '<S10>/Kp4'
   */
  rtb_id_ref = 0.5F * rtb_Delay2 + rtDW.DiscreteTimeIntegrator_DSTATE_o;

  /* Saturate: '<S10>/Saturation2' */
  if (rtb_id_ref > 12.4707661F) {
    rtb_id_ref = 12.4707661F;
  } else if (rtb_id_ref < -12.4707661F) {
    rtb_id_ref = -12.4707661F;
  }

  /* Sum: '<S4>/Sum5' incorporates:
   *  Saturate: '<S10>/Saturation2'
   *  Sum: '<S4>/Sum'
   */
  rtb_DiscreteTimeIntegrator_e = rtb_id_ref + rtb_flag;

  /* Sum: '<S4>/Sum2' */
  rtb_Delay = rtDW.RateTransition2 - rtb_Delay;

  /* Sum: '<S11>/Sum6' incorporates:
   *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
   *  Gain: '<S11>/Kp4'
   */
  rtb_DiscreteTimeIntegrator1 = 1.12F * rtb_Delay +
    rtDW.DiscreteTimeIntegrator_DSTATE_g;

  /* Saturate: '<S11>/Saturation2' */
  if (rtb_DiscreteTimeIntegrator1 > 12.4707661F) {
    /* Sum: '<S4>/Sum3' */
    rtb_DiscreteTimeIntegrator1 = 12.4707661F;
  } else if (rtb_DiscreteTimeIntegrator1 < -12.4707661F) {
    /* Sum: '<S4>/Sum3' */
    rtb_DiscreteTimeIntegrator1 = -12.4707661F;
  }

  /* End of Saturate: '<S11>/Saturation2' */

  /* Fcn: '<S6>/Fcn' */
  rtb_MultiportSwitch = rtb_Tcmp2 * rtb_DiscreteTimeIntegrator_e - rtb_Fcn1 *
    rtb_DiscreteTimeIntegrator1;

  /* Fcn: '<S6>/Fcn1' */
  rtb_Fcn1 = rtb_Fcn1 * rtb_DiscreteTimeIntegrator_e + rtb_Tcmp2 *
    rtb_DiscreteTimeIntegrator1;

  /* MATLAB Function: '<S4>/SVPWM MATLAB Function' incorporates:
   *  Inport: '<Root>/Tpwm'
   *  Inport: '<Root>/v_bus'
   */
  sector = 0;
  rtb_id_ref = 0.0F;
  rtb_Tcmp2 = 0.0F;
  rtb_DiscreteTimeIntegrator_e = 0.0F;
  if (rtb_Fcn1 > 0.0F) {
    sector = 1;
  }

  if ((1.73205078F * rtb_MultiportSwitch - rtb_Fcn1) / 2.0F > 0.0F) {
    sector += 2;
  }

  if ((-1.73205078F * rtb_MultiportSwitch - rtb_Fcn1) / 2.0F > 0.0F) {
    sector += 4;
  }

  switch (sector) {
   case 1:
    T2 = rtU.Tpwm / rtU.v_bus;
    rtb_DiscreteTimeIntegrator1 = (-1.5F * rtb_MultiportSwitch + 0.866025388F *
      rtb_Fcn1) * T2;
    T2 *= 1.5F * rtb_MultiportSwitch + 0.866025388F * rtb_Fcn1;
    break;

   case 2:
    rtb_DiscreteTimeIntegrator1 = (1.5F * rtb_MultiportSwitch + 0.866025388F *
      rtb_Fcn1) * (rtU.Tpwm / rtU.v_bus);
    T2 = -(1.73205078F * rtb_Fcn1 * rtU.Tpwm / rtU.v_bus);
    break;

   case 3:
    rtb_DiscreteTimeIntegrator1 = -((-1.5F * rtb_MultiportSwitch + 0.866025388F *
      rtb_Fcn1) * (rtU.Tpwm / rtU.v_bus));
    T2 = 1.73205078F * rtb_Fcn1 * rtU.Tpwm / rtU.v_bus;
    break;

   case 4:
    rtb_DiscreteTimeIntegrator1 = -(1.73205078F * rtb_Fcn1 * rtU.Tpwm /
      rtU.v_bus);
    T2 = (-1.5F * rtb_MultiportSwitch + 0.866025388F * rtb_Fcn1) * (rtU.Tpwm /
      rtU.v_bus);
    break;

   case 5:
    rtb_DiscreteTimeIntegrator1 = 1.73205078F * rtb_Fcn1 * rtU.Tpwm / rtU.v_bus;
    T2 = -((1.5F * rtb_MultiportSwitch + 0.866025388F * rtb_Fcn1) * (rtU.Tpwm /
            rtU.v_bus));
    break;

   default:
    T2 = rtU.Tpwm / rtU.v_bus;
    rtb_DiscreteTimeIntegrator1 = -((1.5F * rtb_MultiportSwitch + 0.866025388F *
      rtb_Fcn1) * T2);
    T2 = -((-1.5F * rtb_MultiportSwitch + 0.866025388F * rtb_Fcn1) * T2);
    break;
  }

  ta = rtb_DiscreteTimeIntegrator1 + T2;
  if (ta > rtU.Tpwm) {
    rtb_DiscreteTimeIntegrator1 /= ta;
    T2 /= rtb_DiscreteTimeIntegrator1 + T2;
  }

  ta = (rtU.Tpwm - (rtb_DiscreteTimeIntegrator1 + T2)) / 4.0F;
  rtb_DiscreteTimeIntegrator1 = rtb_DiscreteTimeIntegrator1 / 2.0F + ta;
  switch (sector) {
   case 1:
    rtb_id_ref = rtb_DiscreteTimeIntegrator1;
    rtb_Tcmp2 = ta;
    rtb_DiscreteTimeIntegrator_e = T2 / 2.0F + rtb_DiscreteTimeIntegrator1;
    break;

   case 2:
    rtb_id_ref = ta;
    rtb_Tcmp2 = T2 / 2.0F + rtb_DiscreteTimeIntegrator1;
    rtb_DiscreteTimeIntegrator_e = rtb_DiscreteTimeIntegrator1;
    break;

   case 3:
    rtb_id_ref = ta;
    rtb_Tcmp2 = rtb_DiscreteTimeIntegrator1;
    rtb_DiscreteTimeIntegrator_e = T2 / 2.0F + rtb_DiscreteTimeIntegrator1;
    break;

   case 4:
    rtb_id_ref = T2 / 2.0F + rtb_DiscreteTimeIntegrator1;
    rtb_Tcmp2 = rtb_DiscreteTimeIntegrator1;
    rtb_DiscreteTimeIntegrator_e = ta;
    break;

   case 5:
    rtb_id_ref = T2 / 2.0F + rtb_DiscreteTimeIntegrator1;
    rtb_Tcmp2 = ta;
    rtb_DiscreteTimeIntegrator_e = rtb_DiscreteTimeIntegrator1;
    break;

   case 6:
    rtb_id_ref = rtb_DiscreteTimeIntegrator1;
    rtb_Tcmp2 = T2 / 2.0F + rtb_DiscreteTimeIntegrator1;
    rtb_DiscreteTimeIntegrator_e = ta;
    break;
  }

  /* End of MATLAB Function: '<S4>/SVPWM MATLAB Function' */

  /* Outport: '<Root>/Tcm2' incorporates:
   *  Sum: '<S4>/Add1'
   */
  rtY.Tcm2 = rtb_Tcmp2 - rtb_dbA;

  /* MultiPortSwitch: '<S23>/dbC' incorporates:
   *  Constant: '<S4>/Constant4'
   *  Gain: '<S23>/ 5'
   */
  switch (rtb_DataTypeConversion1) {
   case 0:
    rtb_dbA = -1.0E-6;
    break;

   case 1:
    rtb_dbA = -1.0E-6;
    break;

   case 2:
    rtb_dbA = rtb_Saturation;
    break;

   case 3:
    rtb_dbA = 1.0E-6;
    break;

   case 4:
    rtb_dbA = 1.0E-6;
    break;

   default:
    rtb_dbA = -rtb_Saturation;
    break;
  }

  /* End of MultiPortSwitch: '<S23>/dbC' */

  /* Outport: '<Root>/Tcm3' incorporates:
   *  Sum: '<S4>/Add2'
   */
  rtY.Tcm3 = rtb_DiscreteTimeIntegrator_e - rtb_dbA;

  /* MultiPortSwitch: '<S23>/dbA' incorporates:
   *  Constant: '<S4>/Constant4'
   *  Gain: '<S23>/ 1'
   */
  switch (rtb_DataTypeConversion1) {
   case 0:
    rtb_dbA = 1.0E-6;
    break;

   case 1:
    rtb_dbA = -rtb_Saturation;
    break;

   case 2:
    rtb_dbA = -1.0E-6;
    break;

   case 3:
    rtb_dbA = -1.0E-6;
    break;

   case 4:
    rtb_dbA = rtb_Saturation;
    break;

   default:
    rtb_dbA = 1.0E-6;
    break;
  }

  /* End of MultiPortSwitch: '<S23>/dbA' */

  /* MATLAB Function: '<S4>/DirectionLatch' incorporates:
   *  UnitDelay: '<S4>/Unit Delay1'
   */
  if (rtb_alg_reset > 0.5F) {
    rtDW.dir_mem = 1.0F;
    rtDW.positive_count = 0U;
    rtDW.negative_count = 0U;
  } else if (rtb_hfi_ready > 0.5F) {
    if (rtDW.UnitDelay1_DSTATE > 50.0F) {
      rtDW.negative_count = 0U;
      if (rtDW.positive_count < 50) {
        rtDW.positive_count++;
      }

      if (rtDW.positive_count >= 50) {
        rtDW.dir_mem = 1.0F;
      }
    } else if (rtDW.UnitDelay1_DSTATE < -50.0F) {
      rtDW.positive_count = 0U;
      if (rtDW.negative_count < 50) {
        rtDW.negative_count++;
      }

      if (rtDW.negative_count >= 50) {
        rtDW.dir_mem = -1.0F;
      }
    } else {
      rtDW.positive_count = 0U;
      rtDW.negative_count = 0U;
    }
  } else {
    rtDW.positive_count = 0U;
    rtDW.negative_count = 0U;
  }

  /* Sum: '<S15>/Sum5' incorporates:
   *  DiscreteIntegrator: '<S15>/Discrete-Time Integrator'
   */
  rtb_DiscreteTimeIntegrator1 = rtDW.DiscreteTimeIntegrator_DSTATE_e - rtb_alpha;

  /* Saturate: '<S15>/Saturation' */
  if (rtb_DiscreteTimeIntegrator1 > 1.0F) {
    rtb_DiscreteTimeIntegrator1 = 1.0F;
  } else if (rtb_DiscreteTimeIntegrator1 < -1.0F) {
    rtb_DiscreteTimeIntegrator1 = -1.0F;
  }

  /* Gain: '<S15>/H' incorporates:
   *  Saturate: '<S15>/Saturation'
   */
  rtb_hfi_ready = 3.5F * rtb_DiscreteTimeIntegrator1;

  /* DiscreteFilter: '<S15>/Discrete Filter3' */
  rtb_Tcmp2 = rtb_hfi_ready - -0.6F * rtDW.DiscreteFilter3_states;

  /* Sum: '<S15>/Sum6' incorporates:
   *  DiscreteIntegrator: '<S15>/Discrete-Time Integrator1'
   */
  rtb_DiscreteTimeIntegrator_e = rtDW.DiscreteTimeIntegrator1_DSTATE - rtb_beta;

  /* Saturate: '<S15>/Saturation1' */
  if (rtb_DiscreteTimeIntegrator_e > 1.0F) {
    rtb_DiscreteTimeIntegrator_e = 1.0F;
  } else if (rtb_DiscreteTimeIntegrator_e < -1.0F) {
    rtb_DiscreteTimeIntegrator_e = -1.0F;
  }

  /* Gain: '<S15>/H1' incorporates:
   *  Saturate: '<S15>/Saturation1'
   */
  T2 = 3.5F * rtb_DiscreteTimeIntegrator_e;

  /* DiscreteFilter: '<S15>/Discrete Filter2' */
  ta = T2 - -0.6F * rtDW.DiscreteFilter2_states;

  /* Sum: '<S14>/Add' incorporates:
   *  DiscreteFilter: '<S15>/Discrete Filter2'
   *  DiscreteFilter: '<S15>/Discrete Filter3'
   *  DiscreteIntegrator: '<S14>/Discrete-Time Integrator'
   *  Gain: '<S14>/Gain'
   *  MATLAB Function: '<S4>/DirectionLatch'
   *  Product: '<S14>/Product'
   *  Product: '<S14>/Product1'
   *  Product: '<S4>/Product1'
   *  Product: '<S4>/Product2'
   *  Trigonometry: '<S14>/Sin'
   *  Trigonometry: '<S14>/Sin1'
   */
  rtb_DiscreteTimeIntegrator_e = -((0.2F * rtb_Tcmp2 + 0.2F *
    rtDW.DiscreteFilter3_states) * rtDW.dir_mem) * cosf
    (rtDW.DiscreteTimeIntegrator_DSTATE_m) - (0.2F * ta + 0.2F *
    rtDW.DiscreteFilter2_states) * rtDW.dir_mem * sinf
    (rtDW.DiscreteTimeIntegrator_DSTATE_m);

  /* Gain: '<S64>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S56>/Filter'
   *  Gain: '<S54>/Derivative Gain'
   *  Sum: '<S56>/SumD'
   */
  rtb_DiscreteTimeIntegrator1 = (0.0F * rtb_DiscreteTimeIntegrator_e -
    rtDW.Filter_DSTATE) * 0.0F;

  /* Sum: '<S70>/Sum' incorporates:
   *  DiscreteIntegrator: '<S61>/Integrator'
   *  Gain: '<S66>/Proportional Gain'
   */
  rtb_Abs = (80.0F * rtb_DiscreteTimeIntegrator_e + rtDW.Integrator_DSTATE_l) +
    rtb_DiscreteTimeIntegrator1;

  /* Saturate: '<S68>/Saturation' */
  if (rtb_Abs > 1000.0F) {
    rtb_Saturation_f = 1000.0F;
  } else if (rtb_Abs < -1000.0F) {
    rtb_Saturation_f = -1000.0F;
  } else {
    rtb_Saturation_f = rtb_Abs;
  }

  /* End of Saturate: '<S68>/Saturation' */

  /* DiscreteFilter: '<S4>/Discrete Filter5' */
  DiscreteFilter3_tmp_e_p = rtb_Saturation_f - -0.995F *
    rtDW.DiscreteFilter5_states;
  rtb_DiscreteFilter5 = 0.0025F * DiscreteFilter3_tmp_e_p + 0.0025F *
    rtDW.DiscreteFilter5_states;

  /* Sum: '<S53>/SumI2' */
  rtb_SumI2_h = rtb_Saturation_f - rtb_Abs;

  /* Gain: '<S15>/Gain5' */
  rtb_Abs = -1.24F * rtb_DiscreteFilter5;

  /* Product: '<S15>/Product' incorporates:
   *  DiscreteIntegrator: '<S15>/Discrete-Time Integrator1'
   */
  rtb_Product_e = rtb_Abs * rtDW.DiscreteTimeIntegrator1_DSTATE;

  /* Product: '<S15>/Product1' incorporates:
   *  DiscreteIntegrator: '<S15>/Discrete-Time Integrator'
   */
  rtb_Product1_f = rtDW.DiscreteTimeIntegrator_DSTATE_e * rtb_Abs;

  /* Gain: '<S19>/Gain5' incorporates:
   *  Delay: '<S19>/Delay'
   *  Delay: '<S19>/Delay1'
   *  Gain: '<S19>/Gain3'
   *  Sum: '<S19>/Add'
   */
  rtb_Gain5 = ((rtDW.Delay1_DSTATE_d[0] - 2.0F * rtDW.Delay_DSTATE_e) +
               rtb_alpha) * 0.25F;

  /* Signum: '<S19>/Sign' incorporates:
   *  UnitDelay: '<S4>/Unit Delay6'
   */
  if (rtIsNaNF(rtDW.UnitDelay6_DSTATE)) {
    rtb_Abs = (rtNaNF);
  } else if (rtDW.UnitDelay6_DSTATE < 0.0F) {
    rtb_Abs = -1.0F;
  } else {
    rtb_Abs = (real32_T)(rtDW.UnitDelay6_DSTATE > 0.0F);
  }

  /* End of Signum: '<S19>/Sign' */

  /* Gain: '<S19>/Gain6' incorporates:
   *  Delay: '<S19>/Delay2'
   *  Delay: '<S19>/Delay3'
   *  Gain: '<S19>/Gain4'
   *  Sum: '<S19>/Add1'
   */
  rtb_Gain6_l = ((rtDW.Delay3_DSTATE_e[0] - 2.0F * rtDW.Delay2_DSTATE_o) +
                 rtb_beta) * 0.25F;

  /* Sum: '<S17>/Sum1' incorporates:
   *  Delay: '<S19>/Delay4'
   *  Delay: '<S19>/Delay6'
   *  DiscreteIntegrator: '<S17>/Discrete-Time Integrator'
   *  Product: '<S17>/Product'
   *  Product: '<S17>/Product1'
   *  Product: '<S19>/Product'
   *  Product: '<S19>/Product1'
   *  Sum: '<S19>/Sum'
   *  Sum: '<S19>/Sum1'
   *  Trigonometry: '<S17>/Cos'
   *  Trigonometry: '<S17>/Cos1'
   */
  rtb_Abs = (rtb_Gain5 - rtDW.Delay4_DSTATE) * rtb_Abs * sinf
    (rtDW.DiscreteTimeIntegrator_DSTATE) - (rtb_Gain6_l - rtDW.Delay6_DSTATE) *
    rtb_Abs * cosf(rtDW.DiscreteTimeIntegrator_DSTATE);

  /* SampleTimeMath: '<S110>/Tsamp' incorporates:
   *  Gain: '<S106>/Derivative Gain'
   *
   * About '<S110>/Tsamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_Tsamp_f = 0.0F * rtb_Abs * 10000.0F;

  /* Sum: '<S124>/Sum' incorporates:
   *  Delay: '<S108>/UD'
   *  DiscreteIntegrator: '<S115>/Integrator'
   *  Gain: '<S120>/Proportional Gain'
   *  Sum: '<S108>/Diff'
   */
  rtb_Sum_p = (640.0F * rtb_Abs + rtDW.Integrator_DSTATE_j) + (rtb_Tsamp_f -
    rtDW.UD_DSTATE_n);

  /* DiscreteFilter: '<S17>/Discrete Filter2' */
  DiscreteFilter3_tmp_e_e = rtb_Sum_p - -0.994017899F *
    rtDW.DiscreteFilter2_states_b;

  /* DiscreteFilter: '<S17>/Discrete Filter3' incorporates:
   *  DiscreteFilter: '<S17>/Discrete Filter2'
   */
  DiscreteFilter3_tmp_e = ((DiscreteFilter3_tmp_e_e +
    rtDW.DiscreteFilter2_states_b) - -1.99398208F *
    rtDW.DiscreteFilter3_states_d[0]) - 0.994017959F *
    rtDW.DiscreteFilter3_states_d[1];

  /* Gain: '<S112>/Integral Gain' */
  rtb_IntegralGain_m = 8600.0F * rtb_Abs;

  /* Abs: '<S21>/Abs' incorporates:
   *  Delay: '<S21>/Delay'
   *  Delay: '<S21>/Delay1'
   *  Gain: '<S21>/Gain3'
   *  Gain: '<S21>/Gain4'
   *  Gain: '<S21>/Gain5'
   *  Sum: '<S21>/Add'
   */
  rtb_Abs = fabsf(((rtDW.Delay1_DSTATE_c[0] - 2.0F * rtDW.Delay_DSTATE_m) +
                   lambda_target) * 0.25F * 10.0F);

  /* Update for DiscreteIntegrator: '<S21>/PositiveResponseIntegrator' incorporates:
   *  DiscreteIntegrator: '<S21>/NegativeResponseIntegrator'
   *  Product: '<S21>/Product'
   */
  rtDW.PositiveResponseIntegrator_DSTA += rtb_pos_enable * rtb_Abs * 0.0001F;
  if (rtb_alg_reset > 0.0F) {
    rtDW.PositiveResponseIntegrator_Prev = 1;
    rtDW.NegativeResponseIntegrator_Prev = 1;
  } else {
    rtDW.PositiveResponseIntegrator_Prev = 0;
    rtDW.NegativeResponseIntegrator_Prev = 0;
  }

  /* End of Update for DiscreteIntegrator: '<S21>/PositiveResponseIntegrator' */

  /* Update for DiscreteIntegrator: '<S21>/NegativeResponseIntegrator' incorporates:
   *  Product: '<S21>/Product1'
   */
  rtDW.NegativeResponseIntegrator_DSTA += rtb_Abs * rtb_neg_enable * 0.0001F;

  /* Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_DSTATE += 0.0001F * rtb_Sum_p;

  /* Update for Delay: '<S20>/Delay1' */
  rtDW.Delay1_DSTATE[0] = rtDW.Delay1_DSTATE[1];
  rtDW.Delay1_DSTATE[1] = lambda_target;

  /* Update for Delay: '<S20>/Delay' */
  rtDW.Delay_DSTATE = lambda_target;

  /* Update for UnitDelay: '<S4>/Unit Delay' incorporates:
   *  Gain: '<S4>/wm->Nr'
   */
  rtDW.UnitDelay_DSTATE = 2.38732409F * rtb_DiscreteFilter5;

  /* Update for UnitDelay: '<S4>/Unit Delay1' incorporates:
   *  DiscreteFilter: '<S17>/Discrete Filter3'
   *  Gain: '<S17>/Gain'
   *  Gain: '<S4>/wm->Nr1'
   */
  rtDW.UnitDelay1_DSTATE = ((2.0F * rtDW.DiscreteFilter3_states_d[0] +
    DiscreteFilter3_tmp_e) + rtDW.DiscreteFilter3_states_d[1]) * 2.68387268E-8F *
    2.38732409F;

  /* Update for UnitDelay: '<S4>/Unit Delay2' incorporates:
   *  DiscreteIntegrator: '<S14>/Discrete-Time Integrator'
   */
  rtDW.UnitDelay2_DSTATE = rtDW.DiscreteTimeIntegrator_DSTATE_m;

  /* Update for UnitDelay: '<S4>/Unit Delay3' */
  rtDW.UnitDelay3_DSTATE = rtb_Add;

  /* Update for Delay: '<S20>/Delay3' */
  rtDW.Delay3_DSTATE[0] = rtDW.Delay3_DSTATE[1];
  rtDW.Delay3_DSTATE[1] = rtb_q;

  /* Update for Delay: '<S20>/Delay2' */
  rtDW.Delay2_DSTATE = rtb_q;

  /* Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S10>/Kp5'
   */
  rtDW.DiscreteTimeIntegrator_DSTATE_o += 1200.0F * rtb_Delay2 * 0.0001F;
  if (rtDW.DiscreteTimeIntegrator_DSTATE_o > 12.4707661F) {
    rtDW.DiscreteTimeIntegrator_DSTATE_o = 12.4707661F;
  } else if (rtDW.DiscreteTimeIntegrator_DSTATE_o < -12.4707661F) {
    rtDW.DiscreteTimeIntegrator_DSTATE_o = -12.4707661F;
  }

  /* End of Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */

  /* Switch: '<S26>/FixPt Switch' incorporates:
   *  Constant: '<S25>/FixPt Constant'
   *  Sum: '<S25>/FixPt Sum1'
   *  UnitDelay: '<S8>/Output'
   */
  if ((uint8_T)(rtDW.Output_DSTATE + 1U) > 1) {
    /* Update for UnitDelay: '<S8>/Output' incorporates:
     *  Constant: '<S26>/Constant'
     */
    rtDW.Output_DSTATE = 0U;
  } else {
    /* Update for UnitDelay: '<S8>/Output' */
    rtDW.Output_DSTATE++;
  }

  /* End of Switch: '<S26>/FixPt Switch' */

  /* Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S11>/Kp5'
   */
  rtDW.DiscreteTimeIntegrator_DSTATE_g += 1200.0F * rtb_Delay * 0.0001F;
  if (rtDW.DiscreteTimeIntegrator_DSTATE_g > 12.4707661F) {
    rtDW.DiscreteTimeIntegrator_DSTATE_g = 12.4707661F;
  } else if (rtDW.DiscreteTimeIntegrator_DSTATE_g < -12.4707661F) {
    rtDW.DiscreteTimeIntegrator_DSTATE_g = -12.4707661F;
  }

  /* End of Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S14>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_DSTATE_m += 0.0001F * rtb_Saturation_f;

  /* Update for DiscreteIntegrator: '<S15>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S15>/Gain3'
   *  Gain: '<S15>/Gain4'
   *  Gain: '<S15>/Gain6'
   *  Sum: '<S15>/Add'
   */
  rtDW.DiscreteTimeIntegrator_DSTATE_e += (((4000.0F * rtb_MultiportSwitch -
    2400.0F * rtDW.DiscreteTimeIntegrator_DSTATE_e) - rtb_Product_e) - 4000.0F *
    rtb_hfi_ready) * 0.0001F;

  /* Update for DiscreteFilter: '<S15>/Discrete Filter3' */
  rtDW.DiscreteFilter3_states = rtb_Tcmp2;

  /* Update for DiscreteIntegrator: '<S15>/Discrete-Time Integrator1' incorporates:
   *  Gain: '<S15>/Gain7'
   *  Gain: '<S15>/Gain8'
   *  Gain: '<S15>/Gain9'
   *  Sum: '<S15>/Add1'
   */
  rtDW.DiscreteTimeIntegrator1_DSTATE += (((4000.0F * rtb_Fcn1 + rtb_Product1_f)
    - 2400.0F * rtDW.DiscreteTimeIntegrator1_DSTATE) - 4000.0F * T2) * 0.0001F;

  /* Update for DiscreteFilter: '<S15>/Discrete Filter2' */
  rtDW.DiscreteFilter2_states = ta;

  /* Update for DiscreteIntegrator: '<S61>/Integrator' incorporates:
   *  Gain: '<S58>/Integral Gain'
   *  Sum: '<S53>/SumI4'
   */
  rtDW.Integrator_DSTATE_l += (5000.0F * rtb_DiscreteTimeIntegrator_e +
    rtb_SumI2_h) * 0.0001F;

  /* Update for DiscreteIntegrator: '<S56>/Filter' */
  rtDW.Filter_DSTATE += 0.0001F * rtb_DiscreteTimeIntegrator1;

  /* Update for DiscreteFilter: '<S4>/Discrete Filter5' */
  rtDW.DiscreteFilter5_states = DiscreteFilter3_tmp_e_p;

  /* Update for Delay: '<S19>/Delay4' */
  rtDW.Delay4_DSTATE = rtb_Gain5;

  /* Update for Delay: '<S19>/Delay1' */
  rtDW.Delay1_DSTATE_d[0] = rtDW.Delay1_DSTATE_d[1];
  rtDW.Delay1_DSTATE_d[1] = rtb_alpha;

  /* Update for Delay: '<S19>/Delay' */
  rtDW.Delay_DSTATE_e = rtb_alpha;

  /* Update for UnitDelay: '<S4>/Unit Delay6' */
  rtDW.UnitDelay6_DSTATE = rtb_flag;

  /* Update for Delay: '<S19>/Delay6' */
  rtDW.Delay6_DSTATE = rtb_Gain6_l;

  /* Update for Delay: '<S19>/Delay3' */
  rtDW.Delay3_DSTATE_e[0] = rtDW.Delay3_DSTATE_e[1];
  rtDW.Delay3_DSTATE_e[1] = rtb_beta;

  /* Update for Delay: '<S19>/Delay2' */
  rtDW.Delay2_DSTATE_o = rtb_beta;

  /* Update for DiscreteIntegrator: '<S115>/Integrator' */
  rtDW.Integrator_DSTATE_j += 0.0001F * rtb_IntegralGain_m;

  /* Update for Delay: '<S108>/UD' */
  rtDW.UD_DSTATE_n = rtb_Tsamp_f;

  /* Update for DiscreteFilter: '<S17>/Discrete Filter2' */
  rtDW.DiscreteFilter2_states_b = DiscreteFilter3_tmp_e_e;

  /* Update for DiscreteFilter: '<S17>/Discrete Filter3' */
  rtDW.DiscreteFilter3_states_d[1] = rtDW.DiscreteFilter3_states_d[0];
  rtDW.DiscreteFilter3_states_d[0] = DiscreteFilter3_tmp_e;

  /* Update for Delay: '<S21>/Delay1' */
  rtDW.Delay1_DSTATE_c[0] = rtDW.Delay1_DSTATE_c[1];
  rtDW.Delay1_DSTATE_c[1] = lambda_target;

  /* Update for Delay: '<S21>/Delay' */
  rtDW.Delay_DSTATE_m = lambda_target;

  /* End of Outputs for SubSystem: '<S1>/currloop' */

  /* RateTransition: '<S1>/Rate Transition11' */
  if (rtM->Timing.TaskCounters.TID[1] == 0) {
    /* Outputs for Atomic SubSystem: '<S1>/speedloop' */
    /* Switch: '<S5>/Switch' incorporates:
     *  Inport: '<Root>/speedref'
     *  RateTransition: '<S1>/StartupSpeedRateTransition'
     *  Sum: '<S5>/Sum3'
     */
    if (rtb_speed_enable > 0.0F) {
      rtb_pos_enable = rtU.speedref - rtb_n;
    } else {
      rtb_pos_enable = 0.0F;
    }

    /* End of Switch: '<S5>/Switch' */

    /* SampleTimeMath: '<S174>/Tsamp' incorporates:
     *  Gain: '<S170>/Derivative Gain'
     *
     * About '<S174>/Tsamp':
     *  y = u * K where K = 1 / ( w * Ts )
     *   */
    rtb_neg_enable = 0.0F * rtb_pos_enable * 1000.0F;

    /* Sum: '<S188>/Sum' incorporates:
     *  Delay: '<S172>/UD'
     *  DiscreteIntegrator: '<S179>/Integrator'
     *  Sum: '<S172>/Diff'
     */
    rtb_speed_enable = (rtb_pos_enable + rtDW.Integrator_DSTATE) +
      (rtb_neg_enable - rtDW.UD_DSTATE);

    /* Saturate: '<S186>/Saturation' */
    if (rtb_speed_enable > 20.0F) {
      rtb_alg_reset = 20.0F;
    } else if (rtb_speed_enable < -20.0F) {
      rtb_alg_reset = -20.0F;
    } else {
      rtb_alg_reset = rtb_speed_enable;
    }

    /* End of Saturate: '<S186>/Saturation' */

    /* Update for Delay: '<S172>/UD' */
    rtDW.UD_DSTATE = rtb_neg_enable;

    /* Update for DiscreteIntegrator: '<S179>/Integrator' incorporates:
     *  Gain: '<S176>/Integral Gain'
     *  Sum: '<S169>/SumI2'
     *  Sum: '<S169>/SumI4'
     */
    rtDW.Integrator_DSTATE += ((rtb_alg_reset - rtb_speed_enable) + 4.0F *
      rtb_pos_enable) * 0.001F;

    /* End of Outputs for SubSystem: '<S1>/speedloop' */

    /* Update for RateTransition: '<S1>/Rate Transition2' */
    rtDW.RateTransition2_Buffer0 = rtb_alg_reset;
  }

  /* End of RateTransition: '<S1>/Rate Transition11' */
  /* End of Outputs for SubSystem: '<Root>/FOC_Model' */

  /* Outport: '<Root>/switch_n' */
  rtY.switch_n = rtb_n;

  /* Outport: '<Root>/switch_theta' */
  rtY.switch_theta = dtheta;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_Model' */
  /* Outputs for Atomic SubSystem: '<S1>/currloop' */
  /* Outport: '<Root>/Tcm1' incorporates:
   *  Sum: '<S4>/Add3'
   */
  rtY.Tcm1 = rtb_id_ref - rtb_dbA;

  /* End of Outputs for SubSystem: '<S1>/currloop' */

  /* Outport: '<Root>/ModelState' incorporates:
   *  MATLAB Function: '<S1>/StartupManager'
   */
  rtY.ModelState = rtDW.state;

  /* End of Outputs for SubSystem: '<Root>/FOC_Model' */

  /* Outport: '<Root>/ControlReady' */
  rtY.ControlReady = (real32_T)rtb_startup_ready;

  /* Outputs for Atomic SubSystem: '<Root>/FOC_Model' */
  /* Outputs for Atomic SubSystem: '<S1>/currloop' */
  /* Outport: '<Root>/ObserverReady' incorporates:
   *  Constant: '<S2>/Constant'
   *  MATLAB Function: '<S4>/MATLAB Function'
   *  RelationalOperator: '<S2>/Compare'
   */
  rtY.ObserverReady = (rtDW.mode == 2);

  /* End of Outputs for SubSystem: '<S1>/currloop' */
  /* End of Outputs for SubSystem: '<Root>/FOC_Model' */
  rate_scheduler();
}

/* Model initialize function */
void FOC_Model_initialize(void)
{
  /* SystemInitialize for Atomic SubSystem: '<Root>/FOC_Model' */
  /* SystemInitialize for Atomic SubSystem: '<S1>/currloop' */
  /* SystemInitialize for MATLAB Function: '<S4>/DirectionLatch' */
  rtDW.dir_mem = 1.0F;

  /* End of SystemInitialize for SubSystem: '<S1>/currloop' */
  /* End of SystemInitialize for SubSystem: '<Root>/FOC_Model' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
