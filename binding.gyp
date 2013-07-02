{
  'targets': [
    {
      'target_name': 'epeg',
      'sources': [
        'src/epeg.cc',
        'src/epeg_main.c'
      ],
      'libraries': [
        '-ljpeg'
      ]
    }
  ]
}