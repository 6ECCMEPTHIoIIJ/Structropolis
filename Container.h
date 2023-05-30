#pragma once

#include <mutex>
#include <unordered_map>

#include "Singleton.h"

namespace my_game::sources {

	template<class Key, class Value, class Hasher = std::hash<Key>>
	class Container {
	public:
		using Iterator = typename std::unordered_map<Key, Value, Hasher>::iterator;
		using ConstIterator = typename std::unordered_map<Key, Value, Hasher>::const_iterator;

	private:
		mutable std::mutex mutex_;
		std::unordered_map<Key, Value, Hasher> data_;
	public:
		Container() = default;

		Container(const Container& container) : data_(container.data_) {}

		Container(const std::initializer_list<std::pair<Key, Value>>& list) : data_(list.begin(), list.end()) {}

		virtual ~Container() = default;

		bool Has(const Key& key) const
		{
			std::lock_guard lock(mutex_);
			return data_.contains(key);
		}

		const Value* GetValue(const Key& key) const
		{
			if (!Has(key)) 
			{
				return nullptr;
			}

			std::lock_guard lock(mutex_);
			return &data_.at(key);
		}

		const Key* GetKey(const Key& key) const
		{
			if (!Has(key)) 
			{
				return nullptr;
			}

			std::lock_guard lock(mutex_);
			return &data_.find(key)->first;
		}

		bool Add(const Key& key, const Value& value)
		{
			if (Has(key)) 
			{
				return false;
			}

			std::lock_guard lock(mutex_);
			data_.insert({ key, value });
			return true;
		}

		bool Remove(const Key& key)
		{
			if (!Has(key)) {
				return false;
			}

			std::lock_guard lock(mutex_);
			data_.erase(key);
			return true;
		}

		Iterator begin()
		{
			return data_.begin();
		}

		[[nodiscard]]
		ConstIterator begin() const
		{
			return data_.begin();
		}

		Iterator end()
		{
			return data_.end();
		}

		[[nodiscard]]
		ConstIterator end() const
		{
			return data_.end();
		}
	};
}
