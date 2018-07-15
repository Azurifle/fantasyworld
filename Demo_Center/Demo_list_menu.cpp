#include <stdafx.h>
#include "Demo_list_menu.hpp"
#include "Demo_Center.hpp"
#include "Week_12/App.hpp"

namespace G6037599
{
  // ___ static ___________________________________________________________
  void Demo_list_menu::start()
  {
    static auto is_running = false;
    REQUIRE(!is_running);
    is_running = true;

    Demo_center::disable_mouse_editing();
    show_menu();
    run_app();
    press_to_exit();
    
    is_running = false;
  }

  // ___ private ___________________________________________________________
  void Demo_list_menu::show_menu()
  {
    puts(" === Shader App with sound =======================");
    puts("");
    puts("By: Darlyn Sirikasem G6037599");
    puts("");
  }

  void Demo_list_menu::run_app()
  {
    alutInit(nullptr, nullptr);

    const auto BUFFER = alutCreateBufferFromFile("Week_13/Winning.wav");//only .wav
    check_load_sound_error(BUFFER);

    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, BUFFER);//attach the buffer to it
    alSourcePlay(source);//on other process
    check_play_sound(alGetError());

    App app(640, 480, "Rendering a Triangle!!");
    app.run();

    /*ALint status;
    do
    {
      static const auto CHECK_SECONDS = 1.5f;//0.1f
      alutSleep(CHECK_SECONDS);
      alGetSourcei(source, AL_SOURCE_STATE, &status);
    } while (status == AL_PLAYING);*/

    switch (alutExit())
    { 
      case false: fprintf(stderr, "%s\n", alutGetErrorString(alutGetError())); 
        PROMISE(false); default:;
    }
  }

  void Demo_list_menu::check_load_sound_error(const ALuint t_buffer)
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

  void Demo_list_menu::check_play_sound(const ALenum t_error)
  {
    switch (t_error) { case ALUT_ERROR_NO_ERROR: return; default:; }

    fprintf(stderr, "%s\n", alGetString(t_error));
    alutExit(); 
    PROMISE(false);
  }

  void Demo_list_menu::press_to_exit()
  {
    puts("");
    Demo_center::print_centered_header("End of Demo", '=');
    puts("");
    std::cout << "Press <Any key> to exit: ";
    Demo_center::wait_key();
  }
}//G6037599

