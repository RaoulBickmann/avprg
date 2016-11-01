#ifndef ENVELOPE_H
#define ENVELOPE_H


class Envelope
{
    //Testchanges
public:
    enum State{OFF, ON, RELEASE, ATTACK, DECAY, SUSTAIN};
    Envelope();
    void setSampleRate(float sampleRate);
    float process(float input);
    void on();
    void off();
    void setReleaseSeconds(float seconds);
    void setAttackSeconds(float seconds);
    void setDecaySeconds(float seconds);
    void setSustainGainDB(float gain);
private:
    void setState(State state);
private:
    float sampleRate;
    float gain;
    float releaseSeconds;
    float attackSeconds;
    float decaySeconds;
    float sustainGainDB;
    State state;
    float gainFactor;
};

#endif // ENVELOPE_H
