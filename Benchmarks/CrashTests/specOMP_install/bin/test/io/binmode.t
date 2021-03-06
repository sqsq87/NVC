#!specperl -w

BEGIN {
  use TestInit;
#    chdir 't' if -d 't';
#    @INC = qw(. ../lib);
    require './test.pl';
}

use Config;
use Errno;

plan(tests => 9);

ok( binmode(STDERR),            'STDERR made binary' );
if (find PerlIO::Layer 'perlio') {
  ok( binmode(STDERR, ":unix"),   '  with unix discipline' );
} else {
  ok(1,   '  skip unix discipline without PerlIO layers' );
}
ok( binmode(STDERR, ":raw"),    '  raw' );
ok( binmode(STDERR, ":crlf"),   '  and crlf' );

# If this one fails, we're in trouble.  So we just bail out.
ok( binmode(STDOUT),            'STDOUT made binary' )      || exit(1);
if (find PerlIO::Layer 'perlio') {
  ok( binmode(STDOUT, ":unix"),   '  with unix discipline' );
} else {
  ok(1,   '  skip unix discipline without PerlIO layers' );
}
ok( binmode(STDOUT, ":raw"),    '  raw' );
ok( binmode(STDOUT, ":crlf"),   '  and crlf' );

SKIP: {
    skip "no EBADF", 1 if (!exists &Errno::EBADF);

    no warnings 'io';
    $! = 0;
    binmode(B);
    ok($! == &Errno::EBADF);
    binmode(B); # This is just to quiet "typo" warnings -- SPEC CPU
}
