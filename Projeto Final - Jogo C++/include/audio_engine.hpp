#pragma once
#include "note.hpp"
#include "interfaces.hpp"
#include <chrono> // usado para medir durações de tempo e fazer pausas na execução do programa.(sleep_for)
#include <vector>
#include <thread> // usado para executar reprodução de áudio em thread separada (playbackThread_)
#include <atomic>
 
// Controla audio do jogo: sintetiza notas, toca sequencias e gerencia thread.
class AudioEngine : public IAudioSource {
    // Configuracoes basicas usadas na sintese das ondas.
    float       sampleRate_  = 44100.0f;
    float       masterVolume = 0.8f;
    // Estado compartilhado entre o loop do jogo e a thread de playback.
    std::atomic<bool> playing_{false};
    std::thread playbackThread_;
 
    // Síntese por geração de samples (onda senoidal + harmônicos)
    Sound generateTone(float freq, float durationSec) const;
    Sound generateRest(float durationSec) const;
 
public:
    // Abre o dispositivo de audio da raylib ao criar o motor.
    AudioEngine()  { InitAudioDevice(); }
    // Para qualquer playback pendente e libera o dispositivo de audio.
    ~AudioEngine() {
        stop();
        CloseAudioDevice();
    }
 
    // --- IAudioSource ---
    void play()  override { playing_ = true;  }
    void stop()  override {
        playing_ = false;
        if (playbackThread_.joinable()) playbackThread_.join();
    }
    bool isPlaying() const override { return playing_; }
 
    // --- Interface musical ---
    // Toca uma unica nota calculando a duracao a partir do BPM.
    void playNote(const Note& n, float bpm = 80.0f) {
        stop();
        playbackThread_ = std::thread([this, n, bpm]() {
            playing_ = true;
            const float dur = n.durationInBeats() * (60.0f / bpm);
            Sound s = n.isRest() ? generateRest(dur) : generateTone(n.frequency(), dur);
            PlaySound(s);
            std::this_thread::sleep_for(std::chrono::duration<float>(dur));
            StopSound(s);
            UnloadSound(s);
 
            playing_ = false;
        });
    }
 
    // Toca uma lista de notas em uma thread para nao travar a tela.
    void playSequence(const std::vector<Note>& notes, float bpm) {
        // Toca em thread separada para não bloquear o loop do jogo
        stop();
        playbackThread_ = std::thread([this, notes, bpm]() {
            playing_ = true;
            for (const auto& n : notes) {
                if (!playing_) break;
                float dur = n.durationInBeats() * (60.0f / bpm);
                Sound s = n.isRest() ? generateRest(dur) : generateTone(n.frequency(), dur);
                PlaySound(s);
                std::this_thread::sleep_for(std::chrono::duration<float>(dur));
                StopSound(s);
                UnloadSound(s);
            }
            playing_ = false;
        });
    }
 
    // Ajusta volume interno e tambem o volume master da raylib.
    void setVolume(float v) { masterVolume = v; SetMasterVolume(v); }
};