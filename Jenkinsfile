#!/usr/bin/env groovy

// kill pipeline if not done after 5 minutes
timeout(5) {

node {
    // ***************** IMPORTANT ***********************
    // Set the title for the Doxygen-Doku
    def PROJECT_TITLE = "Praktikum Software Engineering, fbi, h_da, WS2022/2023"

    // Set the starting date to the end of the first lab (so all your initial commits are out)
    // use format yyyy-mm-dd
    def GITSTATS_START_DATE = "2022-10-30"
    // ***************************************************

    // Specifying the directories and files needed later
    // Some paths are relative, because a few jenkins plugins need relative paths
    def BUILD_DIR = "${env.WORKSPACE}/cmake-build-debug"
    def INSTALL_DIR = "${env.WORKSPACE}/install"
    def CONFIG_DIR = "${env.WORKSPACE}/config"
    def SOURCE_DIR = "${env.WORKSPACE}/src/main"

    def REPORTS_DIR_REL = "reports"
    def DOXYGEN_DIR_REL = "${REPORTS_DIR_REL}/doxygen"

    def REPORTS_DIR = "${env.WORKSPACE}/${REPORTS_DIR_REL}"
    def GITSTATS_DIR = "${REPORTS_DIR}/gitstats"

    def CCCC_DIR_REL = "${REPORTS_DIR_REL}/cccc"
    def CCCC_DIR = "${env.WORKSPACE}/${CCCC_DIR_REL}"

    def COVERAGE_DIR = "${REPORTS_DIR}/coverage"
    def DOXYGEN_DIR = "${env.WORKSPACE}/${DOXYGEN_DIR_REL}"

    def COMPILER_WARNINGS_LOG_REL = "${REPORTS_DIR_REL}/compiler-warnings.log"
    def DOXYGEN_WARNINGS_LOG_REL = "${DOXYGEN_DIR_REL}/doxygen-warnings.log"
    def CPPCHECK_REPORT_REL = "${REPORTS_DIR_REL}/cppcheck-report.xml"
    def GTEST_REPORT_REL = "${REPORTS_DIR_REL}/gtest-report.xml"

    def COMPILER_WARNINGS_LOG = "${env.WORKSPACE}/${COMPILER_WARNINGS_LOG_REL}"
    def DOXYGEN_WARNINGS_LOG = "${env.WORKSPACE}/${DOXYGEN_WARNINGS_LOG_REL}"
    def CPPCHECK_REPORT = "${env.WORKSPACE}/${CPPCHECK_REPORT_REL}"
    def GTEST_REPORT = "${env.WORKSPACE}/${GTEST_REPORT_REL}"

    def EVALUATION_DIR = "/tmp/SWE/${env.JOB_NAME}"
    def REPOSITORY_URL = scm.userRemoteConfigs[0].url
    def REPOSITORY_CREDENTIALS = scm.userRemoteConfigs[0].credentialsId

    stage("Pull") {
    
        // delete old workspace
        cleanWs deleteDirs: true
        
        echo "********************************"
        echo REPOSITORY_URL
        echo REPOSITORY_CREDENTIALS
        echo "********************************"
        // Pulling the sources from the repository
        // WARNING: Be sure, that you are using the right repository
        // git url: "https://code.fbi.h-da.de/SE/cocktailpro_legacy.git", credentialsId: "b5b0468b-4d7b-46cf-80c8-bb6d45929adb"
        git url: REPOSITORY_URL, credentialsId: "${REPOSITORY_CREDENTIALS}"
    }

/*
    def COCKTAIL_PRO_IMAGE
    stage("Build Docker Image") {
        // Preparing the name to suit the docker image name syntax
        def imageName = env.JOB_NAME
        imageName = imageName.replaceAll(" ", "_")
        imageName = imageName.replaceAll("[^-_a-zA-Z0-9]", "")
        imageName = imageName.replaceAll("^[-_]+", "")
        imageName = imageName.replaceAll("[-_]+\$", "")
        imageName = imageName.replaceAll("_{3,}", "__")
        if (128 < imageName.length()) {
            imageName = imageName.substring(0, 128)
        }
        imageName = imageName.toLowerCase()

        // Building the image with the correct adjusted job name and build number from jenkins as name and tag for the image
        COCKTAIL_PRO_IMAGE = docker.build("${imageName}:${env.BUILD_NUMBER}")
    }
*/
    // Prepare Environment
    stage("Prep. Env.") {

        // Delete the old build directory
        dir("${BUILD_DIR}") {
            deleteDir()
        }

        // Delete the old install directory
        dir("${INSTALL_DIR}") {
            deleteDir()
        }

        // Delete the old evaluation directory
        dir("${EVALUATION_DIR}") {
            deleteDir()
        }

        // Creating needed directories with their needed parents if they are absent
        sh "mkdir -p ${REPORTS_DIR}"
        sh "mkdir -p ${GITSTATS_DIR}"
        sh "mkdir -p ${CCCC_DIR}"
        sh "mkdir -p ${COVERAGE_DIR}"
        sh "mkdir -p ${DOXYGEN_DIR}"
        sh "mkdir -p ${INSTALL_DIR}"
        sh "mkdir -p ${EVALUATION_DIR}"
        
        sh "printenv"
    // } // merge 2 Prepare-Steps

/* // Only for Build in Docker Container
    COCKTAIL_PRO_IMAGE.inside {
	// Any build steps should be inside the docker container
*/
	// stage("Generate CMake Project Buildsystem") { // merge 2 Prepare-Steps
		// Setting up the CMake project and reloading the CMakeLists.txt
		sh "cmake -G 'Unix Makefiles' \
			-S ${env.WORKSPACE} -B ${BUILD_DIR} \
			-DRUN_GTESTS=OFF \
			-DCMAKE_BUILD_TYPE=Debug \
			-DCMAKE_INSTALL_PREFIX='${INSTALL_DIR}' \
			-DDOXYGEN_OUTPUT_DIRECTORY='${DOXYGEN_DIR}' \
			-DDOXYGEN_PROJECT_NAME=CocktailPro \
			-DDOXYGEN_PROJECT_BRIEF='${PROJECT_TITLE}'"
			
		// No concurrent builds
		properties([disableConcurrentBuilds(), [$class: 'JiraProjectProperty']])
	}


    stage("Build") {
    	try {
        // zeigt die Meldungen und bei Error nur die Bugs
        sh "cmake --build ${BUILD_DIR} --target CocktailPro 2> ${COMPILER_WARNINGS_LOG};"
        sh "cat ${COMPILER_WARNINGS_LOG} >&2"
      }
      catch (err) {
      	  sh "cmake --build ${BUILD_DIR} --target CocktailPro"
      	  currentStage.result = 'FAILURE'
      }
	}

	try {
		stage("Doxygen") {
			//sh "cmake --build ${BUILD_DIR} --target CocktailProDoxygen 2>&1 | tee ${DOXYGEN_WARNINGS_LOG}"
			sh "cmake --build ${BUILD_DIR} --target CocktailProDoxygen 2> ${DOXYGEN_WARNINGS_LOG}"
		}
	} catch (err) {
		currentBuild.result = 'SUCCESS'
	}

	try {
		stage("CppCheck") {
				sh "cmake --build ${BUILD_DIR} --target CocktailProCppCheck 2> ${CPPCHECK_REPORT}"
		}
	} catch (err) {
		currentBuild.result = 'SUCCESS'
	}

	try {
		stage("CCCC") {
      // RH 11/2019: --report_mask=pPS fails to create cccc_src.html (links in report are not working)
			//sh "cd ${SOURCE_DIR}; cccc --opt_infile=${CONFIG_DIR}/cccc.opt --outdir=${CCCC_DIR_REL} --html_outfile=${CCCC_DIR}/cccc.html --report_mask=pPS *.cpp *.h; cd ${env.WORKSPACE}"

			// RH 11/2019: changed directory to confine links to name of file (and not src/main/xxx...)
			// RH 11/2019: added report_mask 'L' to create cccc_src.html
			sh "cd ${SOURCE_DIR}; cccc --opt_infile=${CONFIG_DIR}/cccc.opt --outdir=${CCCC_DIR} --report_mask=LpPS *.cpp *.h; cd ${env.WORKSPACE}"
		}
	} catch (err) {
		currentBuild.result = 'SUCCESS'
	}

	try {
		stage("Build Tests") {
			// Build Executable for Test
			sh "cmake --build ${BUILD_DIR} --target CocktailProTest"
		}
	} catch (err) {
  		currentBuild.result = 'UNSTABLE'
  }

  try {
  	stage("Run Tests") {
			// Clear previously generated coverage data
			sh "lcov --zerocounters --directory ${env.WORKSPACE}"
			// Generate base information. Every line is available with a calling count of zero
			sh "lcov --no-external --capture --initial --directory ${env.WORKSPACE} --output-file ${COVERAGE_DIR}/lcov.base.info"
	
			//Execute Test
			dir("${BUILD_DIR}") {
				sh "./CocktailProTest --gtest_output='xml:${GTEST_REPORT}'"
			}
		}
	} catch (err) {
		currentBuild.result = 'UNSTABLE'
	}

    try {		
			stage("Coverage") {
				// Parsing the created .gcda files of CocktailProTest and generating the information file
				sh "lcov --no-external --quiet --capture --directory ${env.WORKSPACE} --output-file ${COVERAGE_DIR}/lcov.test.info"
				// Merging the base information and the test information to prevent that uncalled files vanish in the result
				sh "lcov --add-tracefile ${COVERAGE_DIR}/lcov.base.info --add-tracefile ${COVERAGE_DIR}/lcov.test.info --output-file ${COVERAGE_DIR}/lcov.total.info"
				// Removing not needed files to help student to focus on the right parts
				sh "lcov --quiet --remove ${COVERAGE_DIR}/lcov.total.info '${BUILD_DIR}/*' '${SOURCE_DIR}/Main.*' '${env.WORKSPACE}/src/test/*' '*.h' -o ${COVERAGE_DIR}/lcov.info"
				// Generate the HTML files out of the information
				sh "genhtml --quiet --function-coverage ${COVERAGE_DIR}/lcov.info --output-directory ${COVERAGE_DIR}"
			}
    } catch (err) {
      currentBuild.result = 'SUCCESS'
    }

    stage("Install") {
      sh "cmake --build ${BUILD_DIR} --target install"
    }
/* // Only for Build in Docker Container		
    }
*/


    try {
      stage("Addons") {
      // Gitstat fails if the date is (still) in the future
      Date date = new Date()
      String YESTERDAY = date.previous().format("yyyy-MM-dd")
      echo YESTERDAY
      if (YESTERDAY < GITSTATS_START_DATE){
        GITSTATS_START_DATE = YESTERDAY
        echo GITSTATS_START_DATE
      }
        // Calculate Git-Statistics
        sh "gitstats -c start_date='${GITSTATS_START_DATE}' ${env.WORKSPACE}/src ${GITSTATS_DIR} >> ${GITSTATS_DIR}/gitstats.log"

        // Check for Memory Leaks with Valgrind / memcheck
        /*
        dir("${BUILD_DIR}") {
          //sh "pwd; valgrind --tool=memcheck --leak-check=full --gen-suppressions=all --suppressions=${CONFIG_DIR}/valgrind_suppress.txt --show-reachable=yes --undef-value-errors=yes --track-origins=yes --child-silent-after-fork=no --trace-children=no --error-exitcode=0 --log-file=memcheck.log --xml=yes --xml-file=report.memcheck ./CocktailPro -M"
          sh "pwd; valgrind --verbose --tool=memcheck --leak-check=full --suppressions=${CONFIG_DIR}/valgrind_suppress.txt --show-reachable=yes --undef-value-errors=yes --track-origins=yes --child-silent-after-fork=yes --trace-children=no --log-file=memcheck.log --xml=yes --xml-file=report.memcheck ./CocktailPro -M"
        }
        */
        /*
        dir("${BUILD_DIR}") {
          runValgrind (
                    childSilentAfterFork: true,
                    excludePattern: '',
                    generateSuppressions: false,
                    ignoreExitCode: true,
                    includePattern: '*CocktailPro',
                    outputDirectory: '',
                    outputFileEnding: '.memcheck',
                    programOptions: '-M',
                    removeOldReports: true,
                    suppressionFiles: "${CONFIG_DIR}/valgrind_suppress.txt",
                    tool: [$class: 'ValgrindToolMemcheck',
                      leakCheckLevel: 'full',
                      showReachable: true,
                      trackOrigins: true,
                      undefinedValueErrors: true],
                    traceChildren: true,
                    valgrindExecutable: '',
                    valgrindOptions: '--verbose',
                    workingDirectory: ''
          )
        }
        */
      }
    } catch (err) {
      currentBuild.result = 'SUCCESS'
    }

    try {
		stage("Publish") {
			// Parsing the Console output for Compiler Warnings and the Doxygen Log file
      recordIssues(tools: [doxygen(pattern: "${DOXYGEN_WARNINGS_LOG_REL}"), gcc(pattern: "${COMPILER_WARNINGS_LOG_REL}")])
      //CppCheck über NextGeneration Plugin
      recordIssues(tools: [cppCheck(pattern: '**/cppcheck-report.xml', reportEncoding: 'ISO-8859-1')])

      //CppCheck-Report über CppCheckPlugin
			// publishCppcheck pattern: "${CPPCHECK_REPORT_REL}"
			// Publish Doxygen
			publishHTML([allowMissing: false, alwaysLinkToLastBuild: false, keepAll: false,
						 reportDir   : "${DOXYGEN_DIR}/html", reportFiles: "index.html",
						 reportName  : "Doxygen Document", reportTitles: ""])
			// Publish CCCC Report
			publishHTML([allowMissing: false, alwaysLinkToLastBuild: false, keepAll: false,
						 reportDir   : "${CCCC_DIR_REL}", reportFiles: "cccc.html",
						 reportName  : "CCCC Report", reportTitles: "",
						 escapeUnderscores : false])
			// Publish Code Coverage
			publishHTML([allowMissing: false, alwaysLinkToLastBuild: false, keepAll: false,
						 reportDir   : "${COVERAGE_DIR}", reportFiles: "main/index.html",
						 reportName  : "Code Coverage", reportTitles: ""])
			// Publish Git Statistics
			publishHTML([allowMissing: false, alwaysLinkToLastBuild: false, keepAll: false,
						 reportDir   : "${GITSTATS_DIR}", reportFiles: "index.html",
						 reportName  : "Git Statistics", reportTitles: ""])
			// Publish Google Test Results
			xunit([GoogleTest(deleteOutputFiles: true, failIfNotNew: false,
					pattern: "${GTEST_REPORT_REL}", skipNoTestFiles: false, stopProcessingIfError: false)])

			/*
			// Publish Valgrind results
			dir("${BUILD_DIR}") {pwd;
			        publishValgrind (
                      failBuildOnInvalidReports: false,
                      failBuildOnMissingReports: false,
                      failThresholdDefinitelyLost: '',
                      failThresholdInvalidReadWrite: '',
                      failThresholdTotal: '',
                      pattern: '*.memcheck',
                      publishResultsForAbortedBuilds: false,
                      publishResultsForFailedBuilds: false,
                      sourceSubstitutionPaths: '',
                      unstableThresholdDefinitelyLost: '',
                      unstableThresholdInvalidReadWrite: '',
                      unstableThresholdTotal: ''
                    )
            }
      */
			// Upload files for evaluation
			sh "rm -rf ${EVALUATION_DIR}"
			sh "mkdir ${EVALUATION_DIR}"
			// Copy all csv's and txt's from install-folder - these are ressource files
			// since cp throws an error if there are no such files - suppress all output and exit codes!
			sh "cp -f -v ${INSTALL_DIR}/bin/*.csv ${INSTALL_DIR}/bin/*.txt ${EVALUATION_DIR} >/dev/null || :"
		  // Copy the Binaries from Install-folder
			sh "cp -f -v ${INSTALL_DIR}/bin/CocktailPro ${INSTALL_DIR}/bin/CocktailProTest ${EVALUATION_DIR} >/dev/null || :"
			
			// Activate Chuck Norris
			chuckNorris()
		}
	} catch (err) {
        currentBuild.result = 'SUCCESS'
  }

} // end of node

} // end of timeout
