#include <memory>
namespace cppclass {

template <typename T>
class UniquePtr {
private:
    T *m_ptr{nullptr};  ///< Pointer to stored object.

public:
    /// \brief Arrow operator.
    /// \return Returns pointer to object.
    T *operator->();

    /// \brief Star operator.
    /// \return Returns reference to object.
    T &operator*();

private:
    /// \brief Constructs a unique pointer with internal ptr pointing to null.
    UniquePtr();

    /// \brief Initializes internal ptr with \p ptr.
    UniquePtr(T *ptr);

    /// \brief Transfer ownership of internal ptr.
    UniquePtr(UniquePtr<T> &&other);

    /// \brief Destroys object pointed at by internal ptr.
    ~UniquePtr();

    UniquePtr(const UniquePtr<T> &other) = delete;
};
}  // namespace cppclass
