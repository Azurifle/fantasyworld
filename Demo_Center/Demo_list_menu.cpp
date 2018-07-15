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
    
    while (true)
    {
      show_menu();
      std::cout << "Press <" << static_cast<char>(OPTION_1) << " - "
        << static_cast<char>(OPTION_LAST) << "> or [ESC] to exit: ";
      switch (is_running = choose_option())
      {
      case false: return; default:;
      }
    }
  }

  // ___ private ___________________________________________________________
  void Demo_list_menu::show_menu()
  {
    puts(" === Game Engine Shader App Projects =======================");
    puts("");
    puts("By: Darlyn Sirikasem G6037599");
    puts("\n");
    puts("         //////////////////////////// Demo list ////////////////////////////");
    puts("");
    show_option(OPTION_1, "12 Shader App.");

    puts("         //////////////////////////////////////////////////////////////////");
    puts("\n");
  }

  void Demo_list_menu::show_option(const char t_option, const char* t_name)
  {
    const auto SPACES = 24;
    std::cout << std::setw(SPACES) << std::setfill(' ') << ' '
      << t_option << ". Week " << t_name << std::endl 
      << std::endl;
  }

  bool Demo_list_menu::choose_option()
  {
    while (true)
    {
      const auto OPTION = Demo_center::get_key();
      if (OPTION_1 <= OPTION && OPTION <= OPTION_LAST)
      {
        system("CLS");
        do_option();
        back_to_main_menu();
        return true;
      }

      switch (OPTION)
      {
      case Demo_center::KEY_ESC: return false; default:;
      }
    }
  }

  void Demo_list_menu::do_option()
  {
    //App app(640, 480, "My Game");
    //app.run();

    ALuint source;
    ALenum error;
    ALint status;

    /* Create an AL buffer from the given sound file. */
    ALuint buffer = alutCreateBufferFromFile("");
    if (buffer == AL_NONE)
    {
      error = alutGetError();
      fprintf(stderr, "Error loading file: '%s'\n",
        alutGetErrorString(error));
      alutExit();
      exit(EXIT_FAILURE);
    }

    /* Generate a single source, attach the buffer to it and start playing. */
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);

    /* Normally nothing should go wrong above, but one never knows... */
    error = alGetError();
    if (error != ALUT_ERROR_NO_ERROR)
    {
      fprintf(stderr, "%s\n", alGetString(error));
      alutExit();
      exit(EXIT_FAILURE);
    }

    /* Check every 0.1 seconds if the sound is still playing. */
    do
    {
      alutSleep(0.1f);
      alGetSourcei(source, AL_SOURCE_STATE, &status);
    } while (status == AL_PLAYING);
  }

  void Demo_list_menu::back_to_main_menu()
  {
    puts("");
    Demo_center::print_centered_header("End of Demo", '=');
    puts("");
    std::cout << "Press <ESC> to main menu: ";

    while (true)
    {
      switch (Demo_center::get_key())
      {
      case Demo_center::KEY_ESC: system("CLS"); return; default:;
      }
    }
  }
}//G6037599

