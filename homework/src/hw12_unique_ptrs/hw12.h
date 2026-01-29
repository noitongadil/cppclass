namespace cppclass {
template <typename T>
class UniquePtr {
private:
    T *m_ptr{nullptr};  ///< Pointer to the managed object.

public:
    /// \brief Default constructor. Constructs an empty UniquePtr.
    UniquePtr();

    /// \brief Constructs a UniquePtr that takes ownership of \p ptr.
    /// \param ptr A raw pointer to the object to manage.
    UniquePtr(T *ptr);

    /// \brief Move constructor.
    /// \details Transfers ownership from \p other to this UniquePtr.
    /// \param other An r-value reference to another UniquePtr.
    UniquePtr(UniquePtr<T> &&other);

    /// \brief Move assignment operator.
    /// \details Transfers ownership from \p other to this object.
    UniquePtr &operator=(UniquePtr<T> &&other);

    /// \brief Destructor.
    /// \details If the UniquePtr holds a non-null pointer, the managed object
    ///          is deleted.
    ~UniquePtr();

    /// \brief Dereferences the stored pointer to access members.
    /// \return A pointer to the managed object.
    T *operator->();

    /// \brief Dereferences the stored pointer.
    /// \return A reference to the managed object.
    T &operator*();

    /// \brief Copying is deleted to enforce exclusive ownership.
    UniquePtr(const UniquePtr<T> &other) = delete;
    UniquePtr &operator=(const UniquePtr<T> &other) = delete;
};

/// \brief Constructs an object of type T and wraps it in a UniquePtr.
/// \param args Arguments forwarded to the constructor of T.
template <typename T, typename... Args>
UniquePtr<T> make_unique(Args &&...args);
}  // namespace cppclass
