#include <stdafx.h>
#include "Audio_manager.hpp"

namespace G6037599
{
  //___ static __________________________________________________________________________________________
  Audio Audio_manager::load_or_get_audio(const std::string& t_ref_name, const std::string& t_file_path)
  {
    static Audio_manager instance;

    const auto FOUND_AUDIO = instance.m_audio_collection_.find(t_ref_name);
    if (FOUND_AUDIO != instance.m_audio_collection_.end()) 
    {
      return FOUND_AUDIO->second;
    }

    REQUIRE(!t_file_path.empty());
    const auto AL_BUFFER_ID = alutCreateBufferFromFile(t_file_path.c_str());
    check_load_sound_error(AL_BUFFER_ID);

    ALuint audio_source_id;
    alGenSources(1, &audio_source_id);
    alSourcei(audio_source_id, AL_BUFFER, AL_BUFFER_ID);//attach the buffer to it

    instance.m_audio_collection_[t_ref_name] = audio_source_id;

    return audio_source_id;
  }

  void Audio_manager::play(const Audio t_audio)
  {
    alSourcePlay(t_audio);//on other process
    check_play_sound(alGetError());
  }

  void Audio_manager::pause(const Audio t_audio)
  {
    alSourcePause(t_audio);
    check_play_sound(alGetError());
  }

  void Audio_manager::stop(const Audio t_audio)
  {
    alSourceStop(t_audio);
    check_play_sound(alGetError());
  }

  //___ deconstructor ___________________________________________________________________________________
  Audio_manager::~Audio_manager()
  {
    switch (alutExit())
    {
    case false: fprintf(stderr, "%s\n", alutGetErrorString(alutGetError()));
    PROMISE(false); default:;
    }
    puts("Audio_manager destroyed.");
  }

  //___ private static ___________________________________________________________________________________
  void Audio_manager::check_load_sound_error(const ALuint t_buffer)
  {
    switch (t_buffer)
    {
    case AL_NONE: break;
    default: return;
    }

    fprintf(stderr, "Error loading file: '%s'\n", alutGetErrorString(alutGetError()));
    alutExit();
    PROMISE(false);
  }

  void Audio_manager::check_play_sound(const ALenum t_error)
  {
    switch (t_error) { case ALUT_ERROR_NO_ERROR: return; default:; }

    fprintf(stderr, "%s\n", alGetString(t_error));
    alutExit();
    PROMISE(false);
  }

  //___ private constructor _______________________________________________________________________________
  Audio_manager::Audio_manager()
  {
    alutInit(nullptr, nullptr);
    puts("Audio_manager initialized.");
  }
}//G6037599