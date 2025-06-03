#include <stdbool.h>
#include <stdint.h>
#include "mcc_generated_files/timer/tce0.h"
#include "stepper.h"
#include <math.h>


#define V_OUT                                   (R)*(I_OUT)  /* Output Voltage [mV] */
#define K_COMP                                  (1000000000.0 * (float)KV/(float)K_MODE)


/* Flag set by interrupt */
static volatile bool     time_flag;

#if STEPPING_MODE == MICRO_STEP
#ifndef MICROSTEPS
#define MICROSTEPS 32
#endif
static uint16_t sine_lookup_table[MICROSTEPS];

static void GenerateSineTable(void)
{
    for (uint16_t i = 0; i < MICROSTEPS; i++)
    {
        float angle = ((float)(i + 1) * (M_PI_2)) / (float)MICROSTEPS;
        sine_lookup_table[i] = AMP_TO_U16(sinf(angle));
    }
}
#else /* STEPPING_MODE */
typedef enum
{
    CW_STEP_0 = 0,
    CW_STEP_45 = 1,
    CW_STEP_90 = 2,
    CW_STEP_135 = 3,
    CW_STEP_180 = 4,
    CW_STEP_225 = 5,
    CW_STEP_270 = 6,
    CW_STEP_315 = 7,
    
    
    CCW_STEP_0 = 8,
    CCW_STEP_45 = 9,
    CCW_STEP_90 = 10,
    CCW_STEP_135 = 11,
    CCW_STEP_180 = 12,
    CCW_STEP_225 = 13,
    CCW_STEP_270 = 14,
    CCW_STEP_315 = 15
} step_t;
#endif /* STEPPING_MODE  */

/* Doesn't reset the counter */
#define NO_CMD      false

/* Reset the counter */
#define RESET_CMD   true

/* This function returns true if the delay for the next step expired */
static inline bool CheckSteps(bool reset_cmd, uint32_t actual_speed)
{
    static uint32_t counter = 0;
    uint32_t pre_counter;
    
    if(reset_cmd == RESET_CMD)
    {
        counter = 0;
        return false;
    }
    else
    {
        while(time_flag == false);
        time_flag = false;

        pre_counter = counter;
        counter += actual_speed;
        
        /* This checks for overflow */
        if(counter < pre_counter)
            return true;
        else
            return false;
    }
}

/* If parameter direction is True means that motor will spin in CCW */
static void StepAdvance(bool direction)
{  
    uint16_t a = 0, b = 0, c = 0, d = 0;

#if STEPPING_MODE == FULL_STEP    
    static step_t step = 0;
    /*These masks are correlated with step_t */
    step &= 7;
    if(direction) step |= 8;

    switch(step)
    {
        case CW_STEP_270:   a = DRIVE_FULL; b = DRIVE_ZERO; c = DRIVE_ZERO; d = DRIVE_FULL; step = CW_STEP_180;     break;
        case CW_STEP_180:   a = DRIVE_FULL; b = DRIVE_ZERO; c = DRIVE_FULL; d = DRIVE_ZERO; step = CW_STEP_90;      break;
        case CW_STEP_90:    a = DRIVE_ZERO; b = DRIVE_FULL; c = DRIVE_FULL; d = DRIVE_ZERO; step = 0;               break;
        case CW_STEP_0:     a = DRIVE_ZERO; b = DRIVE_FULL; c = DRIVE_ZERO; d = DRIVE_FULL; step = CW_STEP_270;     break;

        case CCW_STEP_0:    a = DRIVE_ZERO; b = DRIVE_FULL; c = DRIVE_ZERO; d = DRIVE_FULL; step = CCW_STEP_90;     break;                  
        case CCW_STEP_90:   a = DRIVE_ZERO; b = DRIVE_FULL; c = DRIVE_FULL; d = DRIVE_ZERO; step = CCW_STEP_180;    break;
        case CCW_STEP_180:  a = DRIVE_FULL; b = DRIVE_ZERO; c = DRIVE_FULL; d = DRIVE_ZERO; step = CCW_STEP_270;    break;
        case CCW_STEP_270:  a = DRIVE_FULL; b = DRIVE_ZERO; c = DRIVE_ZERO; d = DRIVE_FULL; step = CCW_STEP_0;      break;

        default:            a = DRIVE_ZERO; b = DRIVE_ZERO; c = DRIVE_ZERO; d = DRIVE_ZERO; step = CW_STEP_0;       break; 
    }   
#endif /* STEPPING_MODE==FULL_STEP */

#if STEPPING_MODE == HALF_STEP
    static step_t step = 0;
    /*These masks are correlated with step_t */
    step &= 7;
    if(direction) step |= 8;
    
    switch(step)
    {
        case CW_STEP_315:  a = DRIVE_ZERO; b = DRIVE_HALF; c = DRIVE_ZERO; d = DRIVE_HALF; step = CW_STEP_270;      break;  
        case CW_STEP_270:  a = DRIVE_ZERO; b = DRIVE_ZERO; c = DRIVE_ZERO; d = DRIVE_FULL; step = CW_STEP_225;      break;
        case CW_STEP_225:  a = DRIVE_HALF; b = DRIVE_ZERO; c = DRIVE_ZERO; d = DRIVE_HALF; step = CW_STEP_180;      break;
        case CW_STEP_180:  a = DRIVE_FULL; b = DRIVE_ZERO; c = DRIVE_ZERO; d = DRIVE_ZERO; step = CW_STEP_135;      break;
        case CW_STEP_135:  a = DRIVE_HALF; b = DRIVE_ZERO; c = DRIVE_HALF; d = DRIVE_ZERO; step = CW_STEP_90;       break;
        case CW_STEP_90:   a = DRIVE_ZERO; b = DRIVE_ZERO; c = DRIVE_FULL; d = DRIVE_ZERO; step = CW_STEP_45;       break;
        case CW_STEP_45:   a = DRIVE_ZERO; b = DRIVE_HALF; c = DRIVE_HALF; d = DRIVE_ZERO; step = CW_STEP_0;        break;
        case CW_STEP_0:    a = DRIVE_ZERO; b = DRIVE_FULL; c = DRIVE_ZERO; d = DRIVE_ZERO; step = CW_STEP_315;      break;  
        
        case CCW_STEP_0:   a = DRIVE_ZERO; b = DRIVE_FULL; c = DRIVE_ZERO; d = DRIVE_ZERO; step = CCW_STEP_45;      break;                  
        case CCW_STEP_45:  a = DRIVE_ZERO; b = DRIVE_HALF; c = DRIVE_HALF; d = DRIVE_ZERO; step = CCW_STEP_90;      break;
        case CCW_STEP_90:  a = DRIVE_ZERO; b = DRIVE_ZERO; c = DRIVE_FULL; d = DRIVE_ZERO; step = CCW_STEP_135;     break;
        case CCW_STEP_135: a = DRIVE_HALF; b = DRIVE_ZERO; c = DRIVE_HALF; d = DRIVE_ZERO; step = CCW_STEP_180;     break;
        case CCW_STEP_180: a = DRIVE_FULL; b = DRIVE_ZERO; c = DRIVE_ZERO; d = DRIVE_ZERO; step = CCW_STEP_225;     break;                  
        case CCW_STEP_225: a = DRIVE_HALF; b = DRIVE_ZERO; c = DRIVE_ZERO; d = DRIVE_HALF; step = CCW_STEP_270;     break;
        case CCW_STEP_270: a = DRIVE_ZERO; b = DRIVE_ZERO; c = DRIVE_ZERO; d = DRIVE_FULL; step = CCW_STEP_315;     break;
        case CCW_STEP_315: a = DRIVE_ZERO; b = DRIVE_HALF; c = DRIVE_ZERO; d = DRIVE_HALF; step = CCW_STEP_0;       break;
        
        default:           a = DRIVE_ZERO; b = DRIVE_ZERO; c = DRIVE_ZERO; d = DRIVE_ZERO; step = CW_STEP_0;        break;               
    }    
#endif /* STEPPING_MODE==HALF_STEP */
    
#if STEPPING_MODE == MICRO_STEP
    static uint16_t step = 0;
    uint16_t index = step % MICROSTEPS;
    uint8_t quadrant = (step / MICROSTEPS) & 0x03;
    uint8_t x = (quadrant << 1) | (direction ? 1 : 0);

    switch(x)
    {
        /* CW */
        case 0x00:
            a = 0;
            b = sine_lookup_table[MICROSTEPS - 1 - index];
            c = 0;
            d = sine_lookup_table[index];
            break;
        case 0x02:
            a = sine_lookup_table[index];
            b = 0;
            c = 0;
            d = sine_lookup_table[MICROSTEPS - 1 - index];
            break;
        case 0x04:
            a = sine_lookup_table[MICROSTEPS - 1 - index];
            b = 0;
            c = sine_lookup_table[index];
            d = 0;
            break;
        case 0x06:
            a = 0;
            b = sine_lookup_table[index];
            c = sine_lookup_table[MICROSTEPS - 1 - index];
            d = 0;
            break;

        /* CCW */
        case 0x01:
            a = 0;
            b = sine_lookup_table[MICROSTEPS - 1 - index];
            c = sine_lookup_table[index];
            d = 0;
            break;
        case 0x03:
            a = sine_lookup_table[index];
            b = 0;
            c = sine_lookup_table[MICROSTEPS - 1 - index];
            d = 0;
            break;
        case 0x05:
            a = sine_lookup_table[MICROSTEPS - 1 - index];
            b = 0;
            c = 0;
            d = sine_lookup_table[index];
            break;
        case 0x07:
            a = 0;
            b = sine_lookup_table[index];
            c = 0;
            d = sine_lookup_table[MICROSTEPS - 1 - index];
            break;

        default:
            a = b = c = d = 0;
            break;
    }
    step++;
    step %= (MICROSTEPS * 4);
#endif /* STEPPING_MODE == MICRO_STEP */
    TCE0_CompareAllChannelsBufferedSet(a, b, c, d);
}

/* This function is registered as a callback and must be called once in 50 us. */
void Stepper_TimeTick(void)
{
    time_flag = true;
}


void Stepper_Init(void)
{
    time_flag = false;
#if STEPPING_MODE == MICRO_STEP
    GenerateSineTable();
#endif
    /* Enable hardware scaling accelerator after initialization */
    TCE0_ScaleEnable(true);
    TCE0_AmplitudeSet(DRIVE_ZERO);
    TCE0_CompareAllChannelsBufferedSet(DRIVE_ZERO, DRIVE_ZERO, DRIVE_ZERO, DRIVE_ZERO);
}

static inline void AmplitudeSet(uint16_t amplitude)
{
    if(amplitude > 32768)
        amplitude = 32768;
    TCE0_AmplitudeSet(amplitude);
}

stepper_position_t Stepper_Move(stepper_position_t initial_position, stepper_position_t steps, uint32_t acceleration, uint32_t deceleration, uint32_t speed_limit, uint16_t vbus_mv)
{
    stepper_position_t actual_position = initial_position;
    uint32_t actual_speed = 0;
    bool direction;
    uint32_t steps_to_go;
    uint32_t steps_until_stop = 0;
    
    uint16_t amplitude;
    uint32_t compensation;
   
    /* Preparing the computations */
    if(vbus_mv == 0)
    {
        amplitude    = AMP_TO_U16(0.0);
        compensation = AMP_TO_U16(0.0);
    }
    else if(vbus_mv <= (uint16_t)V_OUT)
    {
        amplitude    = AMP_TO_U16(1.0);
        compensation = AMP_TO_U16(1.0);
    }
    else
    {
        amplitude    = AMP_TO_U16(V_OUT  / (float)vbus_mv);
        compensation = (uint32_t)(K_COMP / (float)vbus_mv);
    }
    
    if(steps < 0)
    {
        direction = true;
        steps_to_go = (uint32_t)(0 - steps);
    }
    else
    {
        direction = false;
        steps_to_go = (uint32_t)steps;
    }

    uint64_t sq_speed_limit = (uint64_t)speed_limit * (uint64_t)speed_limit;
    uint64_t sq_speed_top   = 2 * (uint64_t)acceleration * (uint64_t)deceleration * (uint64_t)steps_to_go * 65536 / (acceleration + deceleration);

    if(sq_speed_top > sq_speed_limit)
    {
        /* Trapezoidal profile: acceleration, constant speed, deceleration */
        steps_until_stop = (uint32_t)(sq_speed_limit / (2 * 65536 * deceleration));
    }
    else
    {
        /* Triangular profile: acceleration, deceleration */
        steps_until_stop = (uint32_t)(acceleration * steps_to_go / (acceleration + deceleration));
    }

    CheckSteps(RESET_CMD, 0);
        
    AmplitudeSet(amplitude);
    
    /* Now start moving */
    while(steps_to_go != 0)
    {
        /* Verifying the speed profile: acceleration, deceleration and constant speed */
        if(steps_to_go > steps_until_stop)
        {
            if(actual_speed < (speed_limit - acceleration))
            {
                actual_speed += acceleration;
            }
            else if(actual_speed < speed_limit) actual_speed++;
        }
        else
        {
            if(actual_speed > deceleration)
            {
                actual_speed -= deceleration;
            }
            else if(actual_speed > 1) actual_speed--;
        }
        uint16_t dynamic_amp = (uint16_t)((compensation * (uint32_t)actual_speed) >> 16);

        AmplitudeSet(amplitude + dynamic_amp);
        
        bool b = CheckSteps(NO_CMD, actual_speed);
        if(b)
        {
            steps_to_go--;
            StepAdvance(direction);
            if(direction) actual_position--;
            else          actual_position++;
        }
    }
    /* Movement completed. Now the motor is stopped. */
    actual_speed = 0;
    AmplitudeSet(amplitude);
    
    /* Release the current through coils */
#if (RELEASE_IN_IDLE == true)
    TCE0_CompareAllChannelsBufferedSet(DRIVE_ZERO, DRIVE_ZERO, DRIVE_ZERO, DRIVE_ZERO);
#endif /* RELEASE_IN_IDLE */
    
    return actual_position;
}

