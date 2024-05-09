{
  'targets': [{
    'target_name': 'libintrusive',
    'type': 'static_library',
    'include_dirs': [
      './include',
    ],
    'sources': [
      './src/list.c',
      './src/queue.c',
      './src/ring.c',
      './src/set.c',
      './src/stack.c',
    ],
    'direct_dependent_settings': {
      'include_dirs': [
        './include',
      ],
    },
    'configurations': {
      'Debug': {
        'defines': ['DEBUG'],
      },
      'Release': {
        'defines': ['NDEBUG'],
      },
    },
  }]
}
