#ifndef G6037599_MEMORY_POOL_HPP
#define G6037599_MEMORY_POOL_HPP
#pragma once

namespace G6037599
{
  class Memory_pool final
  {
  public:
    struct Memory_meta_data final 
    { 
      unsigned usage_size;
      unsigned actual_size;
    };

    Memory_pool();
    explicit Memory_pool(int t_byte_size);
    Memory_pool(const Memory_pool& t_to_copy);
    Memory_pool(Memory_pool&& t_to_move) noexcept;
    ~Memory_pool();
    Memory_pool& operator = (const Memory_pool& t_to_copy);
    Memory_pool& operator = (Memory_pool&& t_to_move) noexcept;

    int get_size() const; //const = this function modify nothing
    void expand();
    void expand(int t_byte_size);
    char* allocate(size_t t_size);
    void add(char t_unicode);
    void print() const;
  private:
    std::vector<char*> m_begin_memories_{}, m_end_memories_{};
    Memory_meta_data m_meta_data_;
    char* m_cursor_;
    int m_byte_size_;
    unsigned m_memories_index_;

    void initialize();
    void copy_from(const Memory_pool& t_to_copy);
    void release();
  };

  void memory_pool_demo();
}//G6037599

#endif //G6037599_MEMORY_POOL_HPP