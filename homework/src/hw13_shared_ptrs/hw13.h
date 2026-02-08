#include <cstddef> // size_t

namespace cppclass {

template <typename T> class WeakPtr;

struct ControlBlock {
    size_t strong_ref_count;
    size_t weak_ref_count;
};

template <typename T>
class SharedPtr {
    friend class WeakPtr<T>;

private:
    T *m_ptr{nullptr};
    ControlBlock *m_cb{nullptr};

public:
    /// \brief Default constructor.
    SharedPtr();

    /// \brief Copy constructor.
    SharedPtr(const SharedPtr &other);

    /// \brief Copy assignment operator.
    SharedPtr &operator=(const SharedPtr &other);

    /// \brief Raw pointer constructor.
    /// \warning Takes ownership of ptr. ptr must be allocated via new.
    SharedPtr(T *ptr);

    /// \brief Move constructor.
    SharedPtr(SharedPtr &&other);

    /// \brief Move assignment operator.
    SharedPtr &operator=(SharedPtr &&other);

    /// \brief Checks if the stored pointer is not null.
    operator bool() const;

    /// \brief Destructor.
    ~SharedPtr();

    /// \brief Dereferences the stored pointer to access members.
    T *operator->() const;

    /// \brief Dereferences the stored pointer.
    T &operator*() const;
};

/// \brief Constructs an object of type T and wraps it in a SharedPtr.
template <typename T, typename... Args>
SharedPtr<T> make_shared(Args &&...args);

template <typename T>
class WeakPtr {
    friend class SharedPtr<T>;

private:
    T *m_ptr{nullptr};
    ControlBlock *m_cb{nullptr};

public:
    /// \brief Default constructor.
    WeakPtr();

    /// \brief Copy constructor.
    WeakPtr(const WeakPtr &other);

    /// \brief Copy assignment.
    WeakPtr &operator=(const WeakPtr &other);

    /// \brief Move constructor.
    WeakPtr(WeakPtr &&other);

    /// \brief Move assignment.
    WeakPtr &operator=(WeakPtr &&other);

    /// \brief Constructs a WeakPtr from a SharedPtr.
    WeakPtr(const SharedPtr<T> &other);
    
    /// \brief Assigns from a SharedPtr.
    /// \note Changed from && to const & (see explanation below).
    WeakPtr &operator=(const SharedPtr<T> &other);

    /// \brief Destructor.
    ~WeakPtr();

    /// \brief Creates a SharedPtr that manages the referenced object.
    SharedPtr<T> lock() const;
};
} // namespace cppclass
