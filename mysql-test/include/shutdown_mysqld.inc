# This is the first half of include/restart_mysqld.inc.
if ($rpl_inited)
{
  if (!$allow_rpl_inited)
  {
    --die ERROR IN TEST: When using the replication test framework (master-slave.inc, rpl_init.inc etc), use rpl_restart_server.inc instead of restart_mysqld.inc. If you know what you are doing and you really have to use restart_mysqld.inc, set allow_rpl_inited=1 before you source restart_mysqld.inc
  }
}

# Write file to make mysql-test-run.pl expect the "crash", but don't start it
--let $_server_id= `SELECT @@server_id`
--let $_expect_file_name= $MYSQLTEST_VARDIR/tmp/mysqld.$_server_id.expect
--exec echo "wait" > $_expect_file_name

# Send shutdown to the connected server.

--let $ss_timeout= 60

if ($shutdown_server_timeout)
{
  --let $ss_timeout= $shutdown_server_timeout
}

--let $timeout_multiplier= 6

if ($VALGRIND_TEST)
{
  --expr $ss_timeout= $ss_timeout * $timeout_multiplier
}

--let $have_sparc = `select convert(@@version_compile_machine using latin1) IN ('sparc')`
if ($have_sparc)
{
  --expr $ss_timeout= $ss_timeout * $timeout_multiplier
}
--shutdown_server $ss_timeout

--source include/wait_until_disconnected.inc

