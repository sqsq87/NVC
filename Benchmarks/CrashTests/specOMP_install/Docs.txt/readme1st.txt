---------------------------------------------------
W A R N I N G      W A R N I N G      W A R N I N G
---------------------------------------------------
The following text file was automatically generated
from a document that you really should read in HTML
format.  This text document is only a poor fallback
if you cannot read HTML, but it is NOT RECOMMENDED.

To read this document in the recommended way, point
your favorite web browser at one of these 3 places:
(1) The SPEC site http://www.spec.org/omp2012/Docs/
(2) The docs directory from your OMP2012 DVD, e.g.:
    /dvdrom/Docs/ for Unix or E:\Docs\ for Windows.
(3) The Docs directory on the system where you have
    installed your SPEC OMP2012 tree - for example:
    /spec/Docs/ (Unix) or D:\myspec\Docs\ (Windows)
---------------------------------------------------
W A R N I N G      W A R N I N G      W A R N I N G
---------------------------------------------------

                          SPEC OMP2012: Read Me First

   Last updated: $Date: 2012-10-11 13:43:55 -0400 (Thu, 11 Oct 2012) $ by
   $Author: BrianWhitney $

   (To check for possible updates to this document, please see
   http://www.spec.org/omp2012/Docs/ )

    Introduction

   This document provides background information about the SPEC OMP2012
   benchmark suite. SPEC hopes that this material will help you understand
   what the benchmark suite can, and cannot, provide; and that it will help
   you make efficient use of the product.

   Overall, SPEC designed SPEC OMP2012 to provide a comparative measure of
   compute intensive performance across the widest practical range of
   hardware. The product consists of source code benchmarks that are
   developed from real user applications. These benchmarks depend on the
   processor, memory and compiler on the tested system.

   This document is organized as a series of questions and answers.

   Background

   Q1. What is SPEC?

   Q2. What is a benchmark?

   Q3. Should I benchmark my own application?

   Q4. If not my own application, then what?

   Scope

   Q5. What does SPEC OMP2012 measure?

   Q6. Why use SPEC OMP2012?

   Q7. What are the limitations of SPEC OMP2012?

   Overview of usage

   Q8. What is included in the SPEC OMP2012 package?

   Q9. What does the user of the SPEC OMP2012 suite have to provide?

   Q10. What are the basic steps in running the benchmarks?

   Q11. What source code is provided? What exactly makes up these suites?

   Metrics

   Q12. Some of the benchmark names sound familiar; are these comparable to
   other programs?

   Q13. What metrics can be measured?

   Q14. What is the difference between a "base" metric and a "peak" metric?

   Q15. What is the power metric?

   Q16. Which SPEC OMP2012 metric should be used to compare performance?

   OMP2012 vs. OMP2001

   Q17. SPEC OMP2001 is already available. Why create SPEC OMP2012? Will it
   show anything different?

   Q18. What happens to SPEC OMP2001 after SPEC OMP2012 is released?

   Q19. Is there a way to translate SPEC OMP2001 results to SPEC OMP2012
   results or vice versa?

   Benchmark selection

   Q20. What criteria were used to select the benchmarks?

   Q21. Weren't some of the SPEC OMP2012 benchmarks in SPEC OMP2001? How are
   they different?

   Q22. Why were some of the benchmarks not carried over from OMP2001?

   Miscellaneous

   Q23. Why does SPEC use a reference machine? What machine is used for SPEC
   OMP2012?

   Q24. How long does it take to run the SPEC OMP2012 benchmark suites?

   Q25. What if the tools cannot be run or built on a system? Can the
   benchmarks be run manually?

   Q26. Where are SPEC OMP2012 results available?

   Q27. Can SPEC OMP2012 results be published outside of the SPEC web site?
   Do the rules still apply?

   Q28. How do I contact SPEC for more information or for technical support?

   Q29. Now that I have read this document, what should I do next?

   Note: links to SPEC OMP2012 documents on this web page assume that you are
   reading the page from a directory that also contains the other SPEC
   OMP2012 documents. If by some chance you are reading this web page from a
   location where the links do not work, try accessing the referenced
   documents at one of the following locations:

     * www.spec.org/omp2012/Docs/
     * The $SPEC/Docs/ (Unix) or %SPEC%\Docs\ (Windows) directory on a system
       where SPEC OMP2012 has been installed.
     * The Docs/ directory on your SPEC OMP2012 distribution media.

    Q1. What is SPEC?

   SPEC is the Standard Performance Evaluation Corporation. SPEC is a
   non-profit organization whose members include computer hardware vendors,
   software companies, universities, research organizations, systems
   integrators, publishers and consultants. SPEC's goal is to establish,
   maintain and endorse a standardized set of relevant benchmarks for
   computer systems. Although no one set of tests can fully characterize
   overall system performance, SPEC believes that the user community benefits
   from objective tests which can serve as a common reference point.

    Q2. What is a benchmark?

   A benchmark is "a standard of measurement or evaluation" (Webster's II
   Dictionary). A computer benchmark is typically a computer program that
   performs a strictly defined set of operations - a workload - and returns
   some form of result - a metric - describing how the tested computer
   performed. Computer benchmark metrics usually measure speed: how fast was
   the workload completed; or throughput: how many workload units per unit
   time were completed. Running the same computer benchmark on multiple
   computers allows a comparison to be made.

    Q3. Should I benchmark my own application?

   Ideally, the best comparison test for systems would be your own
   application with your own workload. Unfortunately, it is often impractical
   to get a wide base of reliable, repeatable and comparable measurements for
   different systems using your own application with your own workload.
   Problems might include generation of a good test case, confidentiality
   concerns, difficulty ensuring comparable conditions, time, money, or other
   constraints.

    Q4. If not my own application, then what?

   You may wish to consider using standardized benchmarks as a reference
   point. Ideally, a standardized benchmark will be portable, and may already
   have been run on the platforms that you are interested in. However, before
   you consider the results you need to be sure that you understand the
   correlation between your application/computing needs and what the
   benchmark is measuring. Are the benchmarks similar to the kinds of
   applications you run? Do the workloads have similar characteristics? Based
   on your answers to these questions, you can begin to see how the benchmark
   may approximate your reality.

   Note: A standardized benchmark can serve as reference point. Nevertheless,
   when you are doing vendor or product selection, SPEC does not claim that
   any standardized benchmark can replace benchmarking your own actual
   application.

    Q5. What does SPEC OMP2012 measure?

   SPEC OMP2012 focuses on compute intensive performance, which means these
   benchmarks emphasize the performance of:

     * the computer processor (CPU),
     * the memory architecture,
     * the parallel support libraries, and
     * the compilers.

   It is important to remember the contribution of the latter three
   components. SPEC OMP performance intentionally depends on more than just
   the processor.

   SPEC OMP2012 contains a suite that focuses on parallel computing
   performance using the OpenMP parallelism standard.

   The suite can be used to measure along the following vector:

     * Compilation method: Consistent compiler options across all programs of
       a given language (the base metrics) and, optionally, compiler options
       tuned to each program (the peak metrics). See Q14, below, for more
       information.

   SPEC OMP2012 is not intended to stress other computer components such as
   networking, the operating system, graphics, or the I/O system. Note that
   there are many other SPEC benchmarks, including benchmarks that
   specifically focus on graphics, distributed Java computing, webservers,
   and network file systems.

    Q6. Why use SPEC OMP2012?

   SPEC OMP2012 provides a comparative measure of parallel performance using
   OpenMP. If this matches with the type of workloads you are interested in,
   SPEC OMP2012 provides a good reference point.

   Other advantages to using SPEC OMP2012 include:

     * The benchmark programs are developed from actual end-user
       applications, as opposed to being synthetic benchmarks.
     * Multiple vendors use the suite and support it.
     * SPEC OMP2012 is highly portable.
     * A wide range of results are available at http://www.spec.org
     * The benchmarks are required to be run and reported according to a set
       of rules to ensure comparability and repeatability.

    Q7. What are the limitations of SPEC OMP2012?

   As described above, the ideal benchmark for vendor or product selection
   would be your own workload on your own application. Please bear in mind
   that no standardized benchmark can provide a perfect model of the
   realities of your particular system and user community.

    Q8. What is included in the SPEC OMP2012 package?

   SPEC provides the following on the SPEC OMP2012 image:

     * Source code for the OMPG2012 benchmarks
     * A tool set for compiling, running, validating and reporting on the
       benchmarks
     * Pre-compiled tools for a variety of operating systems
     * Source code for the SPEC OMP2012 tools, for systems not covered by the
       pre-compiled tools
     * Run and reporting rules defining how the benchmarks should be used to
       produce SPEC OMP2012 results.
     * Documentation

    Q9. What does the user of the SPEC OMP2012 suite have to provide?

   Briefly, you need a Unix, Linux, Mac OS X, or Microsoft Windows system
   with compilers; 8GB of free disk space; and a minimum of 32GB of free
   memory - although more may be required, as described in
   system-requirements.html

    Q10. What are the basic steps in running the benchmarks?

   Installation and use are covered in detail in the SPEC OMP2012 User
   Documentation. The basic steps are:

     * Ensure that you meet the system requirements.
     * Install SPEC OMP2012 from the image on Unix, Linux, Mac OS X (Mac OS
       has not been tested, but may work), or Microsoft Windows (Windows is
       not supported by may work).
     * Determine which metric you wish to run.
     * Learn about runspec, which is the primary SPEC-provided tool.
     * Locate a configuration file as a starting point. Hints about where to
       find one are in runspec.html.
     * Use runspec to build (compile) the benchmarks.
     * If the above steps are successful, use runspec to run, validate, and
       create a report on the performance of the benchmarks.

   If you wish to generate results suitable for quoting in public, you will
   need to carefully study and adhere to the run rules.

    Q11. What source code is provided? What exactly makes up these suites?

   OMPG2012 is based on compute-intensive applications provided as source
   code. OMPG2012 contains 14 benchmarks: 8 use Fortran, 5 use C, and 1 use
   C++. The benchmarks are:

   350.md       Fortran Physics: Molecular Dynamics
   351.bwaves   Fortran Physics: Computational Fluid Dynamics (CFD)
   352.nab      C       Molecular Modeling
   357.bt331    Fortran Physics: Computational Fluid Dynamics (CFD)
   358.botsalgn C       Protein Alignment
   359.botsspar C       Sparse LU
   360.ilbdc    Fortran Lattic Boltzmann
   362.fma3d    Fortran Mechanical Response Simulation
   363.swim     Fortran Weather Prediction
   367.imagick  C       Image Processing
   370.mgrid331 Fortran Physics: Computational Fluid Dynamics (CFD)
   371.applu331 Fortran Physics: Computational Fluid Dynamics (CFD)
   372.smithwa  C       Optimal Pattern Matching
   376.kdtree   C++     Sorting and Searching

   Descriptions of the benchmarks, with reference to papers, web sites, and
   so forth, can be found in the individual benchmark descriptions (click the
   links above). Some of the benchmarks also provide additional details, such
   as documentation from the original program, in the nnn.benchmark/Docs
   directories in the SPEC benchmark tree.

   The numbers used as part of the benchmark names provide an identifier to
   help distinguish programs from one another.

    Q12. Some of the benchmark names sound familiar; are these comparable to
    other programs?

   Many of the SPEC benchmarks have been derived from publicly available
   application programs. The individual benchmarks in this suite may be
   similar, but are NOT identical to benchmarks or programs with similar
   names which may be available from sources other than SPEC. In particular,
   SPEC has invested significant effort to improve portability and to
   minimize hardware dependencies, to avoid unfairly favoring one hardware
   platform over another. For this reason, the application programs in this
   distribution may perform differently from commercially available versions
   of the same application.

   Therefore, it is not valid to compare SPEC OMP2012 benchmark results with
   anything other than other SPEC OMP2012 benchmark results.

    Q13. What metrics can be measured?

   After the benchmarks are run on the system under test (SUT), a ratio for
   each of them is calculated using the run time on the SUT and a
   SPEC-determined reference time. From these ratios, the following metrics
   are calculated:

   OMPG2012 (for OpenMP compute intensive parallel performance comparisons):

     * Compute Performance metrics:

          * SPECompG_base2012: The geometric mean of fourteen normalized
            ratios when the benchmarks are compiled with base tuning.
          * SPECompG_peak2012: The geometric mean of fourteen normalized
            ratios when the benchmarks are compiled with peak tuning.

     * Energy Consumption metrics:

          * SPECompG_energy_base2012: The geometric mean of fourteen
            normalized ratios of the energy used with base tuning.
          * SPECompG_energy_peak2012: The geometric mean of fourteen
            normalized ratios of the energy used with peak tuning.

   In all cases, a higher score means "better performance" on the given
   workload.

    Q14. What is the difference between a "base" metric and a "peak" metric?

   In order to provide comparisons across different computer hardware, SPEC
   provides the benchmarks as source code. Thus, in order to run the
   benchmarks, they must be compiled. There is agreement that the benchmarks
   should be compiled the way users compile programs. But how do users
   compile programs?

     * Some users might experiment with many different compilers and compiler
       flags to achieve the best performance, and may be willing to develop
       multi-step make processes and "training" workloads.

     * Other users might prefer the relative simplicity of using a single set
       of switches and a single-step make process.

   In addition to the above, a wide range of other types of usage models
   could also be imagined, ranging in a continuum from -Odebug at the low
   end, to inserting directives and/or re-writing the source code at the high
   end. Which points on this continuum should SPEC OMP2012 allow?

   SPEC recognizes that any point chosen from that continuum might seem
   arbitrary to those whose interests lie at a different point. Nevertheless,
   choices must be made.

   For OMP2012, SPEC has chosen to allow two types of compilation:

     * The base metrics (e.g. SPECompG_base2012) are required for all
       reported results and have stricter guidelines for compilation. For
       example, the same flags must be used in the same order for all
       benchmarks of a given language. This is the point closer to those who
       might prefer a relatively simple build process.

     * The peak metrics (e.g. SPECompG_peak2012) are optional and have less
       strict requirements. For example, different compiler options may be
       used on each benchmark, and feedback-directed optimization is allowed.
       This point is closer to those who may be willing to invest more time
       and effort in development of build procedures.

   Note that options allowed under the base metric rules are a subset of
   those allowed under the peak metric rules. A legal base result is also
   legal under the peak rules but a legal peak result is NOT necessarily
   legal under the base rules.

   A full description of the distinctions and required guidelines can be
   found in the SPEC OMP2012 Run and Reporting Rules.

    Q15. What is the power metric?

   With OMP2012, SPEC is providing a way to measure the power consumed during
   the benchmark run.

     * The SPECompG_energy_base metric is the normalized power performance
       during the base run.
     * The SPECompG_energy_peak2012 metric is the normalized power
       performance during the peak run.

   The benchmark reports lists many other power measure data.

    Q16. Which SPEC OMP2012 metric should be used to compare performance?

   It depends on your needs. SPEC provides the benchmarks and results as
   tools for you to use. You need to determine how you use a computer or what
   your performance requirements are and then choose the appropriate SPEC
   benchmark or metrics.

    Q17: SPEC OMP2001 is already available. Why create SPEC OMP2012? Will it
    show anything different?

   Technology is always improving. As the technology improves, the benchmarks
   should improve as well. SPEC needed to address the following issues:

   Scaling:
   As of summer, 2012, many of the OMP2001 benchmarks are finishing in less
   than a minute on large parallel system. SPEC has attempted to address this
   with new benchmarks and data sets to have good scaling to 512 OpenMP
   threads while running in a non-trivial amount of time.

   OpenMP new features:
   As the OpenMP standard has changed, additional features have been added.
   OMP2012 attempts to include many of these features.

   Moving target:
   OMP2001 has been available for eleven years and much improvement in
   hardware and software has occurred during this time. Benchmarks need to
   evolve to keep pace with improvements.

   Power measurement:
   OMP2012 includes the optional ability to measure power consumpution during
   the benchmark run.

    Q18: What happens to SPEC OMP2001 after SPEC OMP2012 is released?

   SPEC will begin the process of retiring OMP2001. Three months after the
   announcement of OMP2012, SPEC will require all OMP2001 results submitted
   for publication on SPEC's web site to be accompanied by OMP2012 results.
   Six months after announcement, SPEC will stop accepting OMP2001 results
   for publication on its web site.

    Q19: Is there a way to translate SPEC OMP2001 results to SPEC OMP2012
    results or vice versa?

   There is no formula for converting OMP2001 results to OMP2012 results and
   vice versa; they are different products. There probably will be some
   correlation between OMP2001 and OMP2012 results (i.e., machines with
   higher OMP2001 results often will have higher OMP2012 results), but there
   is no universal formula for all systems.

   SPEC encourages SPEC licensees to publish OMP2012 numbers on older
   platforms to provide a historical perspective on performance.

    Q20: What criteria were used to select the benchmarks?

   In the process of selecting applications to use as benchmarks, SPEC
   considered the following criteria:

     * portability to a variety of CPU architectures (32- and 64-bit
       including AMD64, Intel IA32, Power, SPARC, etc.)
     * portability to various operating systems
     * nearly all of the time is spent compute bound
     * little time spent in IO and system services
     * benchmarks should run in about 32GB RAM without swapping or paging
     * no more than five percent of benchmarking time should be spent
       processing code not provided by SPEC

    Q21: Weren't some of the SPEC OMP2012 benchmarks in SPEC OMP2001? How are
    they different?

   Although some of the benchmarks from OMP2001 are included in OMP2012, they
   all have been given different workloads and/or modified to use newer
   versions of the source code. Therefore, for example, results with the
   OMP2001 benchmark 312.swim_m may be strikingly different from results with
   the OMP2012 benchmark 363.swim.

    Q22: Why were some of the benchmarks not carried over from OMP2001?

   Some benchmarks were not retained because it was not possible to create a
   longer-running or more robust workload. Others were left out because SPEC
   felt that they did not add significant performance information compared to
   the other benchmarks under consideration.

    Q23: Why does SPEC use a reference machine? What machine is used for SPEC
    OMP2012?

   SPEC uses a reference machine to normalize the performance metrics used in
   the OMP2012 suites. Each benchmark is run and measured on this machine to
   establish a reference time for that benchmark. These times are then used
   in the SPEC calculations.

   SPEC uses a historical Sun system, the "Sun Fire X4140" which was
   introduced in 2008, as the reference machine. The reference machine uses
   two quad-core 2.7 GHz AMD Opteron 2384 processors with 32GB of memory.

   It takes about two days to do a rule-conforming run of the base metrics on
   the reference machine.

   Note that when comparing any two systems measured with the OMP2012, their
   performance relative to each other would remain the same even if a
   different reference machine was used. This is a consequence of the
   mathematics involved in calculating the individual and overall (geometric
   mean) metrics.

    Q24: How long does it take to run the SPEC OMP2012 benchmark suites?

   This depends on the suite and the machine that is running the benchmarks.
   As mentioned above, the reference (historical) machine takes on the order
   of 2 days; contemporary machines might take less. Again, though, it
   depends on which metrics are run.

    Q25: What if the tools cannot be run or built on a system? Can the
    benchmarks be run manually?

   To generate rule-compliant results, an approved toolset must be used. If
   several attempts at using the SPEC-provided tools are not successful, you
   should contact SPEC for technical support. SPEC may be able to help you,
   but this is not always possible -- for example, if you are attempting to
   build the tools on a platform that is not available to SPEC.

   If you just want to work with the benchmarks and do not care to generate
   publishable results, SPEC provides information about how to do so.

    Q26: Where are SPEC OMP2012 results available?

   Results for measurements submitted to SPEC are available at
   http://www.spec.org/omp2012.

    Q27: Can SPEC OMP2012 results be published outside of the SPEC web site? Do
    the rules still apply?

   Yes, SPEC OMP2012 results can be freely published if all the run and
   reporting rules have been followed. The OMP2012 license agreement binds
   every purchaser of the suite to the run and reporting rules if results are
   quoted in public. A full disclosure of the details of a performance
   measurement must be provided on request.

   SPEC strongly encourages that results be submitted for publication on
   SPEC's web site, since it ensures a peer review process and uniform
   presentation of all results.

   The run and reporting rules for research and and academic contexts
   recognize that it may not be practical to comply with the full set of
   rules in some contexts. It is always required, however, that non-compliant
   results must be clearly distinguished from rule-compliant results.

    Q28. How do I contact SPEC for more information or for technical support?

   SPEC can be contacted in several ways. For general information, including
   other means of contacting SPEC, please see SPEC's Web Site at:

   http://www.spec.org/

   General questions can be emailed to: info@spec.org
   OMP2012 Technical Support Questions can be sent to:
   omp2012support@spec.org

    Q29. Now that I have read this document, what should I do next?

   If you haven't bought OMP2012, it is hoped that you will consider doing
   so. If you are ready to get started using the suite, then you should pick
   a system that meets the requirements as described in

   system-requirements.html

   and install the suite, following the instructions in

   install-guide-unix.html or
   install-guide-windows.html

   Questions and answers were originally prepared by Kaivalya Dixit of IBM,
   Jeff Reilly of Intel Corp, and John Henning of Oracle. Dixit was the
   long-time President of SPEC, Reilly is Chair of the SPEC CPU Subcommittee,
   and Henning is Vice-Chair/Secretary of the SPEC CPU Subcommittee.

   --------------------------------------------------------------------------

   Copyright 1995-2012 Standard Performance Evaluation Corporation
   All Rights Reserved


