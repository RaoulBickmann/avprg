#include <QDebug>
#include <math.h>
#include "envelope.h"

const float MIN_GAIN_DB = -180;
const float MAX_GAIN_DB = 0;
const float MIN_GAIN = pow(10, MIN_GAIN_DB/20);
const float MAX_GAIN = pow(10, MAX_GAIN_DB/20);

inline float db2gain(float db){
    return pow(10, db/20);
}

inline float gain2db(float gain) {
    return 20*log(gain);
}


Envelope::Envelope()
    : gain(0), sampleRate(0), state(OFF), releaseSeconds(0), gainFactor(0), attackSeconds(0), decaySeconds(0), sustainGainDB(0)
{
    // zu Testzwecken 1 Sekunde
    setReleaseSeconds(1);
    setAttackSeconds(1);
    setDecaySeconds(1);
    setSustainGainDB(-20);
}
void Envelope::setSampleRate(float sampleRate){
    this->sampleRate = sampleRate;
}

void Envelope::setReleaseSeconds(float seconds){
    this->releaseSeconds = seconds;
}

void Envelope::setAttackSeconds(float seconds){
    this->attackSeconds = seconds;
}

void Envelope::setDecaySeconds(float seconds){
    this->decaySeconds = seconds;
}

void Envelope::setSustainGainDB(float gain){
    this->sustainGainDB = gain;
}

void Envelope::on(){
    setState(ATTACK);
}
void Envelope::off(){
    setState(RELEASE);
}

void Envelope::setState(State state){
    this->state = state;
    if (state == OFF){
        gain = 0;
        qDebug() << "OFF";
    }

    // nicht mehr benutzt!
    if (state == ON) {
        gain = gainFactor = 1;
        qDebug() << "ON";
    }
    //

    if (state == RELEASE){
        float gainFactor_dB = fabs(0 - MIN_GAIN_DB)/(sampleRate * releaseSeconds);
        gainFactor = 1/db2gain(gainFactor_dB);
        qDebug() << "RELEASE";
    }
    if (state == ATTACK){
        gain = MIN_GAIN;
        float gainFactor_dB = fabs(0-MIN_GAIN_DB)/(sampleRate * attackSeconds);
        gainFactor = db2gain(gainFactor_dB);
        qDebug() << "ATTACK";
    }
    if (state == DECAY) {
        float gainFactor_dB = fabs(0 - sustainGainDB)/(sampleRate * decaySeconds);
        gainFactor = 1/db2gain(gainFactor_dB);
        qDebug() << "DECAY";
    }
    if(state == SUSTAIN) {
        gainFactor = 1;
        qDebug() << "SUSTAIN";
    }
}

float Envelope::process(float input){
    gain *= gainFactor;
    float output = gain * input;

    if(gain < MIN_GAIN && state == RELEASE) {
        setState(OFF);
    }
    if(gain >= MAX_GAIN && state == ATTACK) {
        setState(DECAY);
    }
    if(gain < db2gain(sustainGainDB) && state == DECAY) {
        setState(SUSTAIN);
    }
    return output;
}
