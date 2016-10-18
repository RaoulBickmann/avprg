#include <math.h>
#include "oscillatorsource.h"



OscillatorSource::OscillatorSource()
{
    audioFormat.setCodec("audio/pcm");
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    audioFormat.setChannelCount(2);
    audioFormat.setSampleSize(32);
    audioFormat.setSampleType(QAudioFormat::Float);
    audioFormat.setSampleRate(44100);
}

void OscillatorSource::setSelectedOscillator(int index){
    oscillator.setType((Oscillator::Type)index);
}
void OscillatorSource::setFrequency(float frequency){
    oscillator.setFrequency(frequency);
}
void OscillatorSource::noteOn(int noteNumber){
    float frequency = 440.0 * pow(2.0, (noteNumber - 69.0)/12.0);
    oscillator.setFrequency(frequency);
    envelope.on();
}
void OscillatorSource::noteOff(){
    envelope.off();
}

void OscillatorSource::setGain(float decibel){
    float gain = pow(10, decibel/20.f);
    oscillator.setGain(gain);
}

void OscillatorSource::setAttackSeconds(float value){
    envelope.setAttackSeconds(value);
}

void OscillatorSource::setDecaySeconds(float value){
    envelope.setDecaySeconds(value);
}

void OscillatorSource::setReleaseSeconds(float value){
    envelope.setReleaseSeconds(value);
}

void OscillatorSource::setSustain_dB(float value){
    envelope.setSustain_dB(value);
}

void OscillatorSource::start(){
    oscillator.initialize(audioFormat.sampleRate());
    envelope.setSampleRate(audioFormat.sampleRate());
}
const QAudioFormat& OscillatorSource::format() const{
    return audioFormat;
}

float OscillatorSource::createSample(){
    float sample = oscillator.getValue();
    sample = envelope.process(sample);
    return sample;
}

qint64 OscillatorSource::read(float** buffer, qint64 numFrames){
    // get audio data for left channel
    for(int i = 0; i < numFrames; i++){
        buffer[0][i] = createSample();
    }
    // copy to other channels
    for(int c = 0; c < audioFormat.channelCount(); c++){
        for(int i = 0; i < numFrames; i++){
            buffer[c][i] = buffer[0][i];
        }
    }
    return numFrames;
}
void OscillatorSource::stop(){}
