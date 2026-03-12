#pragma once

#include <obs.hpp>
#include <string>

static inline OBSWeakSource GetWeakSourceByName(const char *name)
{
	obs_source_t *source = obs_get_source_by_name(name);
	if (!source)
		return nullptr;

	obs_weak_source_t *weak_raw = obs_source_get_weak_source(source);
	OBSWeakSource weak = weak_raw;
	obs_weak_source_release(weak_raw);
	obs_source_release(source);

	return weak;
}

static inline std::string GetWeakSourceName(obs_weak_source_t *weak_source)
{
	std::string name;

	obs_source_t *source = obs_weak_source_get_source(weak_source);
	if (source) {
		name = obs_source_get_name(source);
		obs_source_release(source);
	}

	return name;
}