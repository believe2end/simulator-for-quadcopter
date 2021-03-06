#ifndef IMU_H
#define IMU_H


//#include "Imufilter.h"
#include <QObject>

class QTimer;

#define Imu_RATE           0.025
#define ACCELEROMETER_RATE 0.005
#define GYROSCOPE_RATE     0.005
#define GYRO_MEAS_ERROR    0.3      //Imufilter tuning parameter.

//Gravity at Earth's surface in m/s/s
#define g 9.812865328
//Number of samples to average
#define SAMPLES 4
#define CALIBRATION_SAMPLES 128
//Multiply radians to get degrees.
#define toDegrees(x) (x * 57.2957795)
//Multiply degrees to get radians.
#define toRadians(x) (x * 0.01745329252)
//Full scale resolution on the ADXL345 is 4mg/LSB.
//Multiply ADC count readings from ADXL345 to get acceleration in m/s/s.
#define toAcceleration(x) (x * (4 * g0 * 0.001))
//14.375 LSB/(degrees/sec)
#define GYROSCOPE_GAIN (1 / 14.375)
#define ACCELEROMETER_GAIN (0.004 * g0)

/**
 * Imu consisting of "ADXL345" accelerometer and "ITG-3200" gyroscope to calculate
 * roll, pitch and yaw angles.
 */
class Imu : public QObject
{
    Q_OBJECT
public:
    /**
     * Constructor.
     *
     * @param ImuRate Rate which Imufilter update and Euler angle calculation
     *        occurs.
     * @param gyroscopeMeasurementError Imufilter tuning parameter.
     * @param accelerometerRate Rate at which accelerometer data is sampled.
     * @param gyroscopeRate Rate at which gyroscope data is sampled.
     */
    Imu(float ImuRate,
        double gyroscopeMeasurementError,
        float accelerometerRate,
        float gyroscopeRate);
    /**
     * Get the current roll angle.
     *
     * @return The current roll angle in degrees.
     */
    double getRoll(void);

    /**
     * Get the current pitch angle.
     *
     * @return The current pitch angle in degrees.
     */
    double getPitch(void);

    /**
     * Get the current yaw angle.
     *
     * @return The current yaw angle in degrees.
     */
    double getYaw(void);

    double getGyroX(void);
    double getGyroY(void);
    double getGyroZ(void);

    double getAcclX(void);
    double getAcclY(void);
    double getAcclZ(void);

public slots:
    /**
     * Take a set of samples and average them.
     */
    void sampleAccelerometer(void);

    /**
     * Take a set of samples and average them.
     */
    void sampleGyroscope(void);

    /**
     * Update the filter and calculate the Euler angles.
     */
    void filter(void);

private:
    /**
     * Set up the ADXL345 appropriately.
     */
    void initializeAccelerometer(void);

    /**
     * Calculate the zero g offset.
     */
    void calibrateAccelerometer(void);



    /**
     * Set up the ITG-3200 appropriately.
     */
    void initializeGyroscope(void);

    /**
     * Calculate the bias offset.
     */
    void calibrateGyroscope(void);

    //ADXL345   accelerometer;
    //ITG3200   gyroscope;
    //ImuFilter ImuFilter;

    QTimer *accelerometerTicker;
    QTimer *gyroscopeTicker;
    QTimer *filterTicker;

    float accelerometerRate_;
    float gyroscopeRate_;
    float ImuRate_;

    //Offsets for the gyroscope.
    //The readings we take when the gyroscope is stationary won't be 0, so we'll
    //average a set of readings we do get when the gyroscope is stationary and
    //take those away from subsequent readings to ensure the gyroscope is offset
    //or biased to 0.
    double g_xBias;
    double g_yBias;
    double g_zBias;

    double a_xBias;
    double a_yBias;
    double a_zBias;

    volatile double a_xAccumulator;
    volatile double a_yAccumulator;
    volatile double a_zAccumulator;
    volatile double g_xAccumulator;
    volatile double g_yAccumulator;
    volatile double g_zAccumulator;

    //Accelerometer and gyroscope readings for x, y, z axes.
    volatile double a_x;
    volatile double a_y;
    volatile double a_z;
    volatile double g_x;
    volatile double g_y;
    volatile double g_z;

    //Buffer for accelerometer readings.
    int readings[3];
    int accelerometerSamples;
    int gyroscopeSamples;
};

#endif // IMU_H
