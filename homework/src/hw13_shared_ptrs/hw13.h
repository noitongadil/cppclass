#include <cstddef>  // size_t

namespace cppclass {
struct ControlBlock {
    size_t strong_ref_count;  ///< No. of SharedPtrs managing the object.
    size_t weak_ref_count;  ///< No. of WeakPtrs referencing the control block.
};

template <typename T>
class SharedPtr {
private:
    T *m_ptr{nullptr};            ///< Pointer to the managed object.
    ControlBlock *m_cb{nullptr};  ///< Pointer to the shared control block.

public:
    /// \brief Default constructor. Constructs an empty SharedPtr.
    SharedPtr();

    /// \brief Copy constructor.
    /// \details Shares ownership of the object managed by \p other.
    ///          Increments the strong reference count.
    SharedPtr(const SharedPtr &other);

    /// \brief Copy assignment operator.
    /// \details Shares ownership of the object managed by \p other.
    ///          Increments the strong reference count.
    SharedPtr &operator=(const SharedPtr &other);

    /// \brief Constructs a SharedPtr that takes ownership of \p ptr.
    /// \param ptr A raw pointer to take ownership of.
    SharedPtr(T *ptr);

    /// \brief Move constructor.
    /// \details Transfers ownership from \p other to this object.
    /// \param other An r-value reference to a SharedPtr.
    SharedPtr(SharedPtr &&other);

    /// \brief Move assignment operator.
    /// \details Transfers ownership from \p other to this object.
    SharedPtr &operator=(SharedPtr &&other);

    /// \brief Checks if the stored pointer is not null.
    /// \return true if the SharedPtr manages an object, false otherwise.
    operator bool() const;

    /// \brief Destructor.
    /// \details Decrements the strong reference count. If the count reaches
    ///          zero, the managed object is deleted. If the weak count is also
    ///          zero, the control block is deleted.
    ~SharedPtr();

    /// \brief Dereferences the stored pointer to access members.
    /// \return A pointer to the managed object.
    T *operator->();

    /// \brief Dereferences the stored pointer.
    /// \return A reference to the managed object.
    T &operator*();
};

/// \brief Constructs an object of type T and wraps it in a SharedPtr.
/// \param args Arguments forwarded to the constructor of T.
template <typename T, typename... Args>
SharedPtr<T> make_shared(Args &&...args);

template <typename T>
class WeakPtr {
private:
    T *m_ptr{nullptr};            ///< Pointer to the object.
    ControlBlock *m_cb{nullptr};  ///< Pointer to the shared control block.

public:
    /// \brief Default constructor. Constructs an empty WeakPtr.
    WeakPtr();

    /// \brief Copy constructor.
    /// \details Creates a new WeakPtr that references the same object and
    ///          control block as \p other. Increments the weak reference count.
    WeakPtr(const WeakPtr &other);

    /// \brief Copy assignment operator.
    /// \details Creates a new WeakPtr that references the same object and
    ///          control block as \p other. Increments the weak reference count.
    WeakPtr &operator=(const WeakPtr &other);

    /// \brief Move constructor.
    WeakPtr(WeakPtr &&other);

    /// \brief Move assignment operator.
    WeakPtr &operator=(WeakPtr &&other);

    /// \brief Constructs a WeakPtr from a SharedPtr.
    /// \details The WeakPtr is given the references to the object and control
    ///          block managed by \p other without
    WeakPtr(const SharedPtr<T> &other);

    /// \brief Assigns from a SharedPtr.
    /// \details The WeakPtr is given the references to the object and control
    ///          block managed by \p other without
    WeakPtr &operator=(const SharedPtr<T> &&other);

    /// \brief Destructor.
    /// \details Decrements the weak reference count. If both strong and weak
    ///          counts reach zero, the control block is deleted.
    ~WeakPtr();

    /// \brief Checks if the managed object is still valid.
    operator bool() const;

    /// \brief Creates a SharedPtr that manages the referenced object.
    /// \return A valid SharedPtr if the object exists; otherwise, an empty
    ///         SharedPtr.
    SharedPtr<T> lock();
};
}  // namespace cppclass
