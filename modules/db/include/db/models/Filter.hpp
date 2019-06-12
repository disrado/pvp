#pragma once

#include "db/Aliases.hpp"

namespace db
{
namespace cmp
{


static const std::string EQ = "=";
static const std::string NE = "!=";
static const std::string LE = "<=";
static const std::string GE = ">=";
static const std::string LT = "<";
static const std::string GT = ">";
static const std::string LIKE = "~~";
static const std::string ILIKE = "~~*";
static const std::string NOTLIKE = "!~~";
static const std::string NOTILIKE = "!~~*";


} // namespace cmp


template<typename T = std::string>
class Item final
{
public:
	Item() = default;

	Item(const T& value);
	Item(const T&& value);

	Item(const Item&) = default;
	Item& operator=(const Item&) = default;

	Item(Item&&) = default;
	Item& operator=(Item&&) = default;

public:
	T& Value() &;
	T&& Value() &&;
	const T& Value() const &;
	const T&& Value() const &&;
	
	bool IsInited() const;

	std::string ToSql(std::string_view column, const std::string& op = cmp::EQ) const;
	std::string ToSql(
		std::string_view column, const Escape escape, const std::string& op = cmp::EQ) const;

private:
	T m_value;
	bool m_isInitialized = false;
};


template<typename T = std::string>
class ItemRange final
{
public:
	ItemRange() = default;
	ItemRange(const T& from, const T& to, const bool invert = false);
	ItemRange(const T&& from, const T&& to, const bool invert = false);

	ItemRange(const ItemRange&) = default;
	ItemRange& operator=(const ItemRange&) = default;

	ItemRange(ItemRange&&) = default;
	ItemRange& operator=(ItemRange&&) = default;

public:
	T& From() &;
	T&& From() &&;
	const T& From() const &;
	const T&& From() const &&;

	T& To() &;
	T&& To() &&;
	const T& To() const &;
	const T&& To() const &&;

public:
	std::string ToSql(std::string_view column) const;
	std::string ToSql(std::string_view column, const Escape escape) const;

	void Invert();
	
	bool IsInverted() const;
	bool IsInited() const;

private:
	T m_from;
	T m_to;
	bool m_isInverted = false;
	bool m_isInitialized = false;
};


template<typename T = std::string>
using ItemList = std::list<Item<T>>;


template<typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
std::string ToSql(const ItemList<T>& list, const std::string& column);

template<typename T, std::enable_if_t<!std::is_integral<T>::value>* = nullptr>
std::string ToSql(const ItemList<T>& list, const std::string& column, db::Escape escape);


} // namespace db


#include "../../../src/models/Filter.inl"