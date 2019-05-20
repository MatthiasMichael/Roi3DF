conan install . -if %1 -pr %2

set test_projects=^
test_cuda ^
test_custom_no_operators ^
test_custom_with_operators ^
test_eigen ^
test_osg ^
test_qt

(for %%a in (%test_projects%) do (
	IF NOT EXIST %1.test/%%a (
		mkdir %1.test/%%a
	)
	conan install test/%%a -if %1.test/%%a -pr %2
))

mkdir %1
conan build . -bf %1 -c