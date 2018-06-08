#include "stdafx.h"
#include "Memory_pool.hpp"

namespace G6037599
{
  //___ static _______________________________________________________
  void memory_pool_demo()
  {
    puts(" === start test_memory_allocation ===============================");
    const auto START_BYTE_SIZE = 2;
    Memory_pool something(START_BYTE_SIZE);
    printf("Memory location 0 initialized with size of %d bytes.", something.get_size());
    something.print();
    _getch(); _getch();
    puts(" -------------------------------------------------- ");

    enum Enum { N = 'N', O, P, Q, R};
    something.add(N);
    something.add(O);
    std::cout << N << " & " << O << " added to memory location 0.";
    something.print();

    something.add(P);
    printf(R"('%c' added to memory location 1.)", P);
    puts("Memory location 1 initialized.");
    printf("Now memory pool has size of %d bytes.", something.get_size());
    something.print();
    _getch(); _getch();
    puts(" -------------------------------------------------- ");

    const auto EXPAND_BYTE_SIZE = 100;
    something.expand(EXPAND_BYTE_SIZE);
    puts("Test expanding memory pool 100 bytes");
    printf("Now memory pool has size of %d bytes.", something.get_size());
    something.print();
    _getch(); _getch();
    puts(" -------------------------------------------------- ");

    something.add(Q);
    something.add(R);
    printf(R"('%c' & '%c' added to memory location 1 & 2.)", Q, R);
    something.print();
    _getch(); _getch();
    puts(" -------------------------------------------------- ");
  }

  //___ (de)constructors/operators ____________________________________
  Memory_pool::Memory_pool() : m_meta_data_({0, 0}), m_cursor_(nullptr)
    , m_memories_index_(0)
  {
    const auto DEFAULT_BYTE_SIZE = 1024;
    m_byte_size_ = DEFAULT_BYTE_SIZE;
    initialize();
  }

  Memory_pool::Memory_pool(const int t_byte_size) : m_meta_data_({ 0, 0 })
    , m_cursor_(nullptr), m_byte_size_(t_byte_size), m_memories_index_(0)
  {
    initialize();
  }

  Memory_pool::Memory_pool(const Memory_pool & t_to_copy) 
    : m_meta_data_({ 0, 0 }), m_cursor_(nullptr)
    , m_byte_size_(t_to_copy.m_byte_size_) , m_memories_index_(0)
  {
    initialize();
    copy_from(t_to_copy);
  }

  Memory_pool::Memory_pool(Memory_pool&& t_to_move) noexcept
    : m_meta_data_({ 0, 0 }), m_cursor_(nullptr)
    , m_byte_size_(t_to_move.m_byte_size_) , m_memories_index_(0)
  {
    if (this != &t_to_move)
    {
      initialize();
      copy_from(t_to_move);
      t_to_move.release();
    }
  }

  Memory_pool::~Memory_pool()
  {
    release();
    puts("Memory pool malloc & pointers are freed.");
    puts("");
    puts("Memory pool deleted.");
  }

  Memory_pool & Memory_pool::operator=(const Memory_pool & t_to_copy)
  {
    release();
    m_byte_size_ = t_to_copy.m_byte_size_;
    initialize();
    copy_from(t_to_copy);
    return *this;
  }

  Memory_pool& Memory_pool::operator=(Memory_pool&& t_to_move) noexcept
  {
    if (this != &t_to_move)
    {
      release();
      m_byte_size_ = t_to_move.m_byte_size_;
      initialize();
      copy_from(t_to_move);
      t_to_move.release();
    }
    return *this;
  }

  //___ public _______________________________________________________
  int Memory_pool::get_size() const { return m_byte_size_; }

  void Memory_pool::expand()
  {
    expand(m_byte_size_);
  }

  void Memory_pool::expand(const int t_byte_size)
  {
    m_begin_memories_.push_back(reinterpret_cast<char*>(malloc(t_byte_size)));
    m_end_memories_.push_back(m_begin_memories_.back() + t_byte_size);
    m_byte_size_ += t_byte_size;
  }

  char* Memory_pool::allocate(const size_t t_size)
  {
    const auto ALLOCATED = m_cursor_;

    m_meta_data_.usage_size += t_size;
    std::cout << "Allocated: " << t_size << " bytes." << std::endl;

    const auto ALIGN = 4;
    //memory alignment (fastway)
    m_meta_data_.actual_size = m_meta_data_.usage_size + (ALIGN - 1) & -ALIGN;

    //memory alignment (easy but slow)
    /*const auto OFFSET = m_meta_data_.usage_size % ALIGN
      , PADDING = ALIGN - OFFSET;
    if (OFFSET > 0)
    {
      //the memory is not aligned
      m_meta_data_.actual_size = m_meta_data_.usage_size + PADDING;
    }*/

    m_cursor_ += t_size;
    return ALLOCATED;
  }

  void Memory_pool::add(const char t_unicode)
  {
    if (m_cursor_ >= m_end_memories_[m_memories_index_])
    {
      ++m_memories_index_;
      if (m_memories_index_ >= m_end_memories_.size())
      {
        expand();
      }
      m_cursor_ = m_begin_memories_[m_memories_index_];
    }

    *allocate(sizeof(char)) = t_unicode;
  }

  void Memory_pool::print() const
  {
    for (unsigned i = 0; i < m_begin_memories_.size(); ++i)
    {
      std::cout << std::endl << std::endl 
        << " --- Printing memory location " << i << "." << std::endl;
      for (auto cursor = m_begin_memories_[i]; cursor < m_end_memories_[i]; ++cursor)
      {
        std::cout << *cursor;
      }
    }
    std::cout << std::endl << std::endl << "Usage: " << m_meta_data_.usage_size 
      << " bytes, Actual size: " << m_meta_data_.actual_size << " bytes." << std::endl
      << std::endl;
  }

  //___ private _______________________________________________________
  void Memory_pool::initialize()
  {
    m_begin_memories_.push_back(reinterpret_cast<char*>(malloc(m_byte_size_)));
    m_end_memories_.push_back(m_begin_memories_.front() + m_byte_size_);
    m_cursor_ = m_begin_memories_.back();
  }

  void Memory_pool::copy_from(const Memory_pool& t_to_copy)
  {
    for (unsigned memories_index = 0;
      memories_index <= t_to_copy.m_memories_index_;
      ++memories_index)
    {
      for (auto cursor = t_to_copy.m_begin_memories_[memories_index];
        cursor < t_to_copy.m_end_memories_[memories_index]; ++cursor)
      {
        if(memories_index < t_to_copy.m_memories_index_
          || cursor < t_to_copy.m_cursor_)
        {
          add(*cursor);
        }//if still behind other
      }
    }//for each memory
  }

  void Memory_pool::release()
  {
    for (m_memories_index_ = 0; 
      m_memories_index_ < m_begin_memories_.size(); ++m_memories_index_)
    {
      for (m_cursor_ = m_begin_memories_[m_memories_index_];
        m_cursor_ < m_end_memories_[m_memories_index_]; ++m_cursor_)
      {
        const auto CLEAN_MEMORY = 0;
        *m_cursor_ = CLEAN_MEMORY;//just clean this location (4 bytes)
      }

      free(m_begin_memories_[m_memories_index_]);
    }

    m_cursor_ = nullptr;
    m_memories_index_ = 0;
    m_meta_data_.usage_size = 0;
    m_meta_data_.actual_size = 0;
  }

}//G6037599