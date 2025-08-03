#pragma once

#include <switch.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// Audio types
enum class AudioType {
    SFX,
    MUSIC,
    VOICE
};

// Audio format
enum class AudioFormat {
    PCM_16BIT,
    PCM_24BIT,
    PCM_32BIT,
    ADPCM
};

// Audio properties
struct AudioProperties {
    int sampleRate;
    int channels;
    AudioFormat format;
    int bitDepth;
    
    AudioProperties(int rate = 48000, int ch = 2, AudioFormat fmt = AudioFormat::PCM_16BIT, int bits = 16)
        : sampleRate(rate), channels(ch), format(fmt), bitDepth(bits) {}
};

// Sound effect
struct SoundEffect {
    std::string name;
    std::vector<uint8_t> data;
    AudioProperties properties;
    float volume;
    float pitch;
    bool loop;
    
    SoundEffect() : volume(1.0f), pitch(1.0f), loop(false) {}
};

// Music track
struct MusicTrack {
    std::string name;
    std::vector<uint8_t> data;
    AudioProperties properties;
    float volume;
    float fadeInTime;
    float fadeOutTime;
    bool loop;
    
    MusicTrack() : volume(1.0f), fadeInTime(0.0f), fadeOutTime(0.0f), loop(true) {}
};

class AudioManager {
public:
    AudioManager();
    ~AudioManager();
    
    // Initialization
    bool initialize();
    void shutdown();
    
    // Audio loading
    bool loadSoundEffect(const std::string& name, const std::string& filename);
    bool loadMusicTrack(const std::string& name, const std::string& filename);
    void unloadAudio(const std::string& name);
    
    // Sound effect playback
    void playSoundEffect(const std::string& name, float volume = 1.0f, float pitch = 1.0f);
    void stopSoundEffect(const std::string& name);
    void stopAllSoundEffects();
    
    // Music playback
    void playMusic(const std::string& name, float fadeInTime = 0.0f);
    void stopMusic(float fadeOutTime = 0.0f);
    void pauseMusic();
    void resumeMusic();
    
    // Volume control
    void setMasterVolume(float volume);
    void setSFXVolume(float volume);
    void setMusicVolume(float volume);
    float getMasterVolume() const;
    float getSFXVolume() const;
    float getMusicVolume() const;
    
    // Audio state
    bool isMusicPlaying() const;
    bool isSoundEffectPlaying(const std::string& name) const;
    std::string getCurrentMusic() const;
    
    // Update
    void update();
    
    // Switch-specific
    void setAudioOutputMode(int channels, int sampleRate);
    void enable3DAudio(bool enabled);
    bool is3DAudioEnabled() const;
    
private:
    // Nintendo audio
    AudrenDriver driver;
    AudioRendererConfig config;
    AudioRenderer renderer;
    
    // Audio buffers
    std::unordered_map<std::string, std::unique_ptr<SoundEffect>> soundEffects;
    std::unordered_map<std::string, std::unique_ptr<MusicTrack>> musicTracks;
    
    // Playback state
    std::string currentMusic;
    bool musicPaused;
    float musicFadeTimer;
    bool musicFadingOut;
    
    // Volume settings
    float masterVolume;
    float sfxVolume;
    float musicVolume;
    
    // 3D audio
    bool threeDAudioEnabled;
    
    // Private methods
    bool initializeAudren();
    void cleanupAudren();
    
    bool loadAudioFile(const std::string& filename, std::vector<uint8_t>& data, AudioProperties& properties);
    bool loadWavFile(const std::string& filename, std::vector<uint8_t>& data, AudioProperties& properties);
    bool loadOggFile(const std::string& filename, std::vector<uint8_t>& data, AudioProperties& properties);
    
    void updateMusicFade(float deltaTime);
    void processAudioBuffer();
    
    // Utility
    float clampVolume(float volume) const;
    void applyVolume(float& volume) const;
};