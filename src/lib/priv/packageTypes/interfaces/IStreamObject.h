#ifndef ISTREAMOBJECT_H
#define ISTREAMOBJECT_H

#include <QtCore/qglobal.h>
#include <memory>
#include <vector>

#include <priv/IStreamable.h>

#include "StreamObjectTypes.h"

namespace libmson {
namespace fsshttpb {

class IStreamObject;

typedef std::shared_ptr<IStreamObject> IStreamObject_SPtr_t;
typedef std::weak_ptr<IStreamObject> IStreamObject_WPtr_t;

typedef std::vector<IStreamObject_SPtr_t>::iterator IStreamObj_It_t;
typedef std::vector<IStreamObject_SPtr_t>::const_iterator IStreamObj_const_It_t;


class IStreamObject : public priv::IStreamable {
protected:
  /** return the size in bytes of the data contained in this StreamObject,
   * excluding the size of the StreamObjectHeader and StreamObjectHeaderEnd*/
  virtual quint64 strObjBody_cb() const = 0;
  virtual quint64 cbNextHeader() const = 0;


  std::vector<IStreamObject_SPtr_t> m_children{};


  bool m_isParsed = false;
  /// indicates whether m_cb needs to be recalculated, since this value is
  /// needed often during writing
  bool m_isChanged = false;

  /// cache for this size in file
  quint64 m_cb = 0;

  /// Stores length from StreamObjectHeader
  /// indicates the count of bytes till the next StreamObjectHeader or
  /// StreamObjectHeaderEnd
  quint64 m_cbNxtHd = 0;

  IStreamObject() = default;

public:
  virtual ~IStreamObject() = default;

  quint64 getSizeInFile();
  quint64 getCbNextHeader();
  virtual StreamObjectType getType() const = 0;

  bool isCompound() const;

  /**
   * @brief getObjects returns all the child objects
   * @return
   */
  std::vector<IStreamObject_WPtr_t> getObjects();

  /** returns a vector only of the objects which have the same type_info as ti*/
  std::vector<IStreamObject_WPtr_t> getObjects(StreamObjectType type) const;


  /** remove objects of the given type from the children vector */
  void removeObjects(StreamObjectType type);

  // std::vector adapters ######################################################

  /** equivalent to std::vector::at if this is a compound, otherwise
   * default weak_ptr is returned*/
  IStreamObject_WPtr_t at(size_t pos);

  /** returns true if there are no child objects, or if this is not a compound*/
  bool isEmpty();

  /** returns the size of the children vector, or 0 if this is not a compound*/
  size_t size() const;


  /** equivalent to std::vector::begin if this is a compound, otherwise
   * vector.end() is returned*/
  IStreamObj_It_t begin();
  IStreamObj_const_It_t cbegin() const;

  /** equivalent to std::vector::end() */
  IStreamObj_It_t end();
  IStreamObj_const_It_t cend() const;


  /** equivalent to std::vector::push_back if this is a compound, otherwise no
   * operation is performed*/
  virtual void push_back(IStreamObject_SPtr_t& obj) = 0;

  /** equivalent to std::vector::pop_back if this is a compound, otherwise no
   * operation is performed*/
  void pop_back();

  /** equivalent to std::vector::insert if this is a compound, otherwise
   * vector.end() is returned*/
  virtual IStreamObj_It_t
  insert(IStreamObj_It_t pos, const IStreamObject_SPtr_t& obj) = 0;

  /** equivalent to std::vector::erase if this is a compound, otherwise
   * vector.end() is returned*/
  IStreamObj_It_t erase(IStreamObj_It_t pos);

  /** equivalent to std::vector::clear if this is a compound, otherwiseno
   * operation is performed*/
  void clear();

  void setIsChanged();
  bool isChanged() const;
  bool isParsed() const;

private:
  /**
   * @brief deserializes the body of the StreamObject excluding Header, End
   * @param ds
   */
  virtual void deserializeStrObj(QDataStream& ds) = 0;

  /**
   * @brief deserializes the body of the StreamObject excluding Header, End
   * @param ds
   */
  virtual void serializeStrObj(QDataStream& ds) const = 0;

protected:
  //  std::vector<IStreamObject_SPtr_t> parseStreamObjects(QDataStream& ds,
  //  StreamObjectType type);

  bool isObjectStreamEnd(QDataStream& ds);

  bool isObjectStreamEnd(StreamObjectType type, QDataStream& ds);


  // IStreamable interface
private:
  virtual void deserialize(QDataStream& ds) override;
  virtual void serialize(QDataStream& ds) const override;
};


} // namespace fsshttpb
} // namespace libmson

#endif // ISTREAMOBJECT_H
